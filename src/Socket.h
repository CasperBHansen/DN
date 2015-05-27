/*
 * Datanet
 *
 * Socket.h
 *
 */

#ifndef SOCKET_H
#define SOCKET_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string>

#include "SocketException.h"

const int MAX_HOSTNAME      = 128;
const int MAX_CONNECTIONS   = 1;
const int MAX_RECEIVE       = 1024;

class Socket
{
public:
    Socket();
    virtual ~Socket();

    bool bind(const int port);
    bool listen() const;
    bool accept(Socket& new_socket) const;
    bool connect(const std::string host, const int port);

    bool send(const std::string str) const;
    int receive(std::string& str) const;

    void set_non_blocking(const bool b);

private:
    int sock;
    sockaddr_in addr;
};

#endif // SOCKET_H

