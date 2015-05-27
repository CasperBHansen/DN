/*
 * Datanet
 *
 * ServerSocket.cpp
 *
 */

#include "ServerSocket.h"

ServerSocket::ServerSocket(int port)
{
    if (!Socket::bind(port))
        throw SocketException("Could not bind to port.");

    if (!Socket::listen())
        throw SocketException("Could not listen to socket.");
}

ServerSocket::~ServerSocket()
{
}

void ServerSocket::accept(Socket& socket)
{
    if (!Socket::accept(socket))
        throw SocketException("Could not accept socket.");
}

const ServerSocket& ServerSocket::operator>>(HttpRequest& request) const
{
    std::string raw;
    if (!Socket::receive(raw))
        throw SocketException("Could not read from socket.");
    
    if (raw.length() > 0)
        request = HttpRequest(raw);
    
    return (* this);
}

const ServerSocket& ServerSocket::operator<<(const HttpResponse& response) const
{
    if (!Socket::send(response))
        throw SocketException("Could not write to socket.");
    
    return (* this);
}

