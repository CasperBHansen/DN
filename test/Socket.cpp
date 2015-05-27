/*
 * Datanet
 *
 * Socket.cpp
 *
 */

#include "Socket.h"

#include <iostream>
#include <memory.h>
#include <errno.h>
#include <fcntl.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>

Socket::Socket()
      : sock(-1)
{
    memset (&addr, 0, sizeof(addr));
    
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1)
        throw SocketException("Could not create server socket.");;

    int on = 1;
    if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (const char *)&on, sizeof(on) ) == -1)
        throw SocketException("Could not create server socket.");
}

Socket::~Socket()
{
    if (sock != -1) ::close(sock);
}

bool Socket::bind(const int port)
{
    if (sock == -1) return false;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port);
    return (::bind(sock, (struct sockaddr *)&addr, sizeof(addr)) != -1);
}

bool Socket::listen() const
{
    if (sock == -1) return false;
    return (::listen(sock, MAXCONNECTIONS) != -1);
}

bool Socket::accept(Socket& new_socket) const
{
    int addr_length = sizeof(addr);
    new_socket.sock = ::accept(sock, (sockaddr *)&addr, (socklen_t *)&addr_length);
    return (new_socket.sock > 0);
}

bool Socket::send(const std::string str) const
{
    int status = ::send(sock, str.c_str(), str.size(), MSG_NOSIGNAL);
    return (status != -1);
}

int Socket::receive(std::string& str) const
{
    char buffer[MAXRECV + 1];
    str = "";
    memset(buffer, 0, MAXRECV + 1);
    int status = ::recv(sock, buffer, MAXRECV, 0);

    if (status == -1)
    {
        std::cout << "status == -1   errno == " << errno << "  in Socket::recv\n";
        return 0;
    }
    
    if (status != 0) str = buffer;
    
    return status;
}

bool Socket::connect(const std::string host, const int port)
{
    if (sock == -1) return false;

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);

    int status = inet_pton(AF_INET, host.c_str(), &addr.sin_addr);

    if (errno == EAFNOSUPPORT) return false;

    status = ::connect(sock, (sockaddr *)&addr, sizeof(addr));
    return !status;
}

void Socket::set_non_blocking(const bool b)
{
    int opts = fcntl(sock, F_GETFL);
    if (opts < 0) return;
    opts = b ? (opts | O_NONBLOCK) : (opts & ~O_NONBLOCK);
    fcntl(sock, F_SETFL, opts);
}

const Socket& Socket::operator<<(const std::string& str) const
{
    if (!send(str))
        throw SocketException("Could not write to socket.");

    return (* this);
}

const Socket& Socket::operator>>(std::string& str) const
{
    if (!receive(str))
        throw SocketException("Could not read from socket.");

    return (* this);
}
