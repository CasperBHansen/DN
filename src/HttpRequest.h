/*
 * Datanet
 *
 * HttpRequest.h
 *
 */

#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

#include <stdint.h>
#include <iostream>
#include <string>
#include <map>

#include "HttpMessage.h"

// HTTP Methods
enum HttpMethod {
    HTTP_METHOD_OPTIONS     = (1 << 0),
    HTTP_METHOD_GET         = (1 << 1),
    HTTP_METHOD_HEAD        = (1 << 2),
    HTTP_METHOD_POST        = (1 << 3),
    HTTP_METHOD_PUT         = (1 << 4),
    HTTP_METHOD_DELETE      = (1 << 5),
    HTTP_METHOD_TRACE       = (1 << 6),
    HTTP_METHOD_CONNECT     = (1 << 7)
};

std::ostream& operator<<(std::ostream& stream, const HttpMethod& method);

class HttpRequest : public HttpMessage
{
public:
    HttpRequest();
    HttpRequest(const std::string& raw);
	~HttpRequest();

    const HttpMethod getMethod() const;
    const std::string& getURI() const;
    
    std::string& getValue(const std::string& key);
    
    void parse(const std::string& line);
    
protected:
    // request
    std::map<std::string, std::string> request;

private:
    // header
    HttpMethod method;
    std::string uri;
};

std::ostream& operator<<(std::ostream& os, const HttpRequest& request);

#endif // HTTPREQUEST_H

