/*
 * Datanet
 *
 * ClientSocket.cpp
 *
 */

#include "ClientSocket.h"

ClientSocket::ClientSocket(std::string host, int port)
{
    if (!Socket::connect(host, port))
        throw SocketException("Could not bind to port.");
}

