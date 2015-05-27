/*
 * Datanet - main.cpp
 */

#define REQ_ARGS 3

#define PROG_ARG argv[0]
#define PORT_ARG argv[1]
#define ROOT_ARG argv[2]

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

#include <string>
using std::string;

#include <exception>
using std::exception;

#include "Server.h"

int main(int argc, char * argv[]) {
    
    // validate arguments
    if (argc != REQ_ARGS) {
        cerr << "Usage: " << PROG_ARG << " <port>" << endl;
        return EXIT_FAILURE;
    }
    
    // port argument
    string str(PORT_ARG);
    int port = stoi(str, nullptr, 10);
    
    // root directory argument
    string dir(ROOT_ARG);
    
    int ret;
    try {
        
        Server server(port, dir); 
        ret = server.run();
    }
    catch (exception &e) {
        
        cerr << "Exception: " << e.what() << endl;
    }
    
    return ret;
}
