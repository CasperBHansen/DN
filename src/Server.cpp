/*
 * Datanet
 *
 * Server.cpp
 *
 */

#include "Server.h"

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <magic.h>
#include <dirent.h>

#include <iostream>
using std::ostream;
using std::cout;
using std::cerr;
using std::endl;

#include <fstream>
using std::ifstream;

using std::string;

Server::Server(int p, string directory)
      : port(p), root(directory), running(true)
{
    cout << "Serving contents of '" << root << "' at port " << port << ".." << endl;
}

Server::~Server()
{
    cout << "Server shutting down.." << endl;
}

int Server::run()
{
    while (running)
    {
        try {
            
            ServerSocket server(port);
            while (running) {
                
                ServerSocket socket;
                server.accept(socket);
                
                int pid = fork();
                if (pid < 0)
                    throw std::runtime_error("Couldn't fork process");
                
                if (pid != 0) // parent process
                    continue;
                
                try {
                    
                    while (running) {
                        HttpRequest request;
                        socket >> request;
                        
                        if (!request.isValid())
                            continue;
                        
                        cout << "Received: " << endl << request << endl << endl;
                        
                        HttpResponse response;
                        switch (request.getMethod())
                        {
                            case HTTP_METHOD_HEAD:
                                response = get(request.getURI());
                                response.stripContent();
                                break;
                            
                            case HTTP_METHOD_GET:
                                response = get(request.getURI());
                                break;
                            
                            default:
                                response = HttpResponse(HTTP_NOT_IMPLEMENTED);
                                break;
                        }
                        
                        socket << response;
                        
                        cout << "Response:" << endl << (std::string)response << endl;
                    }
                }
                catch (HttpException &e) {
                    cerr << "Exception occured: " << e.what() << endl;
                    socket << HttpResponse(e.which(), e.html());
                    exit(e.which());
                }
                catch (SocketException &e) {
                    // cerr << "Exception occured: " << e.what() << endl;
                    // socket << HttpResponse(HTTP_INTERNAL_SERVER_ERROR);
                    exit(HTTP_INTERNAL_SERVER_ERROR);
                }
                
                exit(0);
            }
        }
        catch (std::runtime_error &e) {
            cerr << "Fatal run-time error: " << e.what() << endl;
            running = false;
        }
    }
    
    return 0;
}

HttpResponse Server::get(const string& path) const
{
    string filepath = root + path;
    string content;
    
    if (path.back() == '/')
        filepath += "index.html";
    
    ifstream file;
    file.open(filepath);
    
    if (!file.is_open())
    {
        // serve a list of files
        content += "<html><head><title>404 - Not Found</title></head><body><ul>";
        DIR * dir = opendir((root + path).c_str());
        struct dirent * entry;
        if (dir != NULL) {
            string filename;
            while ( (entry = readdir(dir)) ) {
                filename = string(entry->d_name);
                filepath = string(root + path) + filename;
                struct stat st;
                lstat(filepath.c_str(), &st);
                if ( (st.st_mode & S_IFMT) == S_IFDIR)
                    filename += '/';
                content += "<li><a href=\"" + filename + "\">" + filename + "</a></li>";
            }
        }
        content += "</ul></body></html>";
        return HttpResponse(HTTP_NOT_FOUND, content);
    }
    
    // get the mime
    string mime;
    magic_t magic = magic_open(MAGIC_MIME_TYPE);
    magic_load(magic, NULL);
    mime = magic_file(magic, filepath.c_str());
    magic_close(magic);
    
    // get the size
    size_t length;
    file.seekg(0, file.end);
    length = file.tellg();
    file.seekg(0, file.beg);
    
    // read contents
    char * buffer = new char[length];
    buffer[length] = '\0';
    file.read(buffer, length);
    file.close();
    content = buffer;
    delete [] buffer;
    
    return HttpResponse(HTTP_OK, content, mime);
}

