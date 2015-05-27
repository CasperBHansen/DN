/*
 * Datanet
 *
 * ServerSocket.h
 *
 */

#ifndef SERVERSOCKET_H
#define SERVERSOCKET_H

#include "Socket.h"

#include "HttpRequest.h"
#include "HttpResponse.h"

class ServerSocket : public Socket
{
public:
    ServerSocket(int port);
    ServerSocket() {};
    virtual ~ServerSocket();

    void accept(Socket& socket);

    const ServerSocket& operator>>(HttpRequest& request) const;
    const ServerSocket& operator<<(const HttpResponse& response) const;
};

#endif // SERVERSOCKET_H

