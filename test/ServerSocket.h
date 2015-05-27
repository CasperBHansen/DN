/*
 * Datanet
 *
 * ServerSocket.h
 *
 */

#ifndef SERVERSOCKET_H
#define SERVERSOCKET_H

#include "Socket.h"

class ServerSocket : public Socket
{
public:
    ServerSocket(int port);
    ServerSocket() {};
    virtual ~ServerSocket();

    void accept(Socket& socket);
};

#endif // SERVERSOCKET_H

