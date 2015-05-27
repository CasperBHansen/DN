/*
 * Datanet
 *
 * SocketException.h
 *
 */

#ifndef SOCKETEXCEPTION_H
#define SOCKETEXCEPTION_H

#include <exception>
#include <string>

class SocketException : public std::exception
{
public:
	SocketException(std::string str);
	~SocketException();
    
    virtual const char * what() throw();

protected:
private:
    std::string msg;
};

#endif // SOCKETEXCEPTION_H

