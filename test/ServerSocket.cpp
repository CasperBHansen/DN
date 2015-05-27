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

