/*
 * Datanet
 *
 * HttpException.h
 *
 */

#ifndef HTTPEXCEPTION_H
#define HTTPEXCEPTION_H

#include <exception>
#include <string>

// TODO: does not belong here, should be moved!
enum HttpResponseCode {
    
    // 2XX - Success Codes
    HTTP_OK                     = 200,
    
    // 4XX - Client Errors
    HTTP_BAD_REQUEST            = 400,
    HTTP_UNAUTHORIZED,
    HTTP_FORBIDDEN              = 403,
    HTTP_NOT_FOUND,
    
    // 5XX - Server Errors
    HTTP_INTERNAL_SERVER_ERROR  = 500,
    HTTP_NOT_IMPLEMENTED
};

class HttpException : public std::exception
{
public:
	HttpException(HttpResponseCode status, std::string str);
	~HttpException();
    
    virtual const char * what() throw();
    virtual const HttpResponseCode which() throw();
    virtual const std::string html() throw();

protected:
private:
    HttpResponseCode code;
    std::string msg;
};

#endif // HTTPEXCEPTION_H

