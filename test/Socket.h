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

const int MAXHOSTNAME = 256;
const int MAXCONNECTIONS = 32;
const int MAXRECV = 512;

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

    virtual const Socket& operator<<(const std::string& str) const;
    virtual const Socket& operator>>(std::string& str) const;

private:
    int sock;
    sockaddr_in addr;
};

#endif // SOCKET_H

