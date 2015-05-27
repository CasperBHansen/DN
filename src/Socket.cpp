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

    int bind_return = ::bind(sock, (struct sockaddr *)&addr, sizeof(addr));
    return (bind_return != -1);
}

bool Socket::listen() const
{
    if (sock == -1) return false;

    int listen_return = ::listen(sock, MAX_CONNECTIONS);
    return (listen_return != -1);
}

bool Socket::accept(Socket& new_socket) const
{
    int addr_length = sizeof(addr);
    new_socket.sock = ::accept(sock, (sockaddr *)&addr, (socklen_t *)&addr_length);
    new_socket.set_non_blocking(true);
    return (new_socket.sock > 0);
}

bool Socket::send(const std::string str) const
{
    int status = ::send(sock, str.c_str(), str.size(), MSG_NOSIGNAL);
    return (status != -1);
}

int Socket::receive(std::string& str) const
{
    int status, length = 0;
    char buffer[MAX_RECEIVE];
    str = "";
    
    while ( (status = ::recv(sock, buffer, MAX_RECEIVE - 1, 0)) > 0) {
        str += buffer;
        length += status;
        memset(buffer, 0, MAX_RECEIVE);
    }
    
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

