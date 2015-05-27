/*
 * Datanet
 *
 * SocketException.cpp
 *
 */

#include "SocketException.h"

SocketException::SocketException(std::string str)
               : msg(str)
{
}

SocketException::~SocketException() {}

const char * SocketException::what() throw()
{
    return msg.c_str();
}

