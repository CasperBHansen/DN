/*
 * Datanet
 *
 * Server.h
 *
 */

#ifndef SERVER_H
#define SERVER_H

#include <string>

#include "ServerSocket.h"

class Server
{
public:
	Server(int port, std::string directory);
	~Server();
    
    int run();
    
protected:
    HttpResponse get(const std::string& path) const;
    
    int port;
    std::string root;
    
private:
    bool running;
};

#endif // SERVER_H

