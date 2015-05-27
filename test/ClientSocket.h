/*
 * Datanet
 *
 * ClientSocket.h
 *
 */

#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H

#include "Socket.h"

class ClientSocket : public Socket
{
public:

    ClientSocket (std::string host, int port);
    virtual ~ClientSocket() {};
};

#endif // CLIENTSOCKET_H

