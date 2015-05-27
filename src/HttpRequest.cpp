/*
 * Datanet
 *
 * HttpRequest.cpp
 *
 */

#include "HttpRequest.h"

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

#include <sstream>
using std::istringstream;
using std::stringstream;
using std::string;

#include <string.h>

#define HTTP_SUPPORTED_METHODS (HTTP_METHOD_GET|HTTP_METHOD_HEAD)

std::ostream& operator<<(std::ostream& stream, const HttpMethod& method)
{
    switch (method)
    {
        case HTTP_METHOD_OPTIONS:
            stream << "OPTIONS";
            break;
        
        case HTTP_METHOD_GET:
            stream << "GET";
            break;
        
        case HTTP_METHOD_HEAD:
            stream << "HEAD";
            break;
        
        case HTTP_METHOD_POST:
            stream << "POST";
            break;
        
        case HTTP_METHOD_PUT:
            stream << "PUT";
            break;
        
        case HTTP_METHOD_DELETE:
            stream << "DELETE";
            break;
        
        case HTTP_METHOD_TRACE:
            stream << "TRACE";
            break;
        
        case HTTP_METHOD_CONNECT:
            stream << "CONNECT";
            break;
            
        default:
            break;
    }
    
    return stream;
}

HttpRequest::HttpRequest()
           : method((HttpMethod)0), uri("")
{
}

HttpRequest::HttpRequest(const string& raw)
           : method((HttpMethod)0), uri("")
{
    istringstream is(raw);
    string line;
    
    std::getline(is, line);
    
    char method_str[8], uri_str[256];
    int matches = sscanf(line.c_str(), "%s %s HTTP/ %i . %i",
                         method_str, uri_str, &version.major, &version.minor);
    
    if (matches != 4)
        throw HttpException(HTTP_BAD_REQUEST, "Illformed request");
    
    if      (strcmp(method_str, "OPTIONS") == 0)    method = HTTP_METHOD_OPTIONS;
    else if (strcmp(method_str, "GET") == 0)        method = HTTP_METHOD_GET;
    else if (strcmp(method_str, "HEAD") == 0)       method = HTTP_METHOD_HEAD;
    else if (strcmp(method_str, "POST") == 0)       method = HTTP_METHOD_POST;
    else if (strcmp(method_str, "PUT") == 0)        method = HTTP_METHOD_PUT;
    else if (strcmp(method_str, "DELETE") == 0)     method = HTTP_METHOD_DELETE;
    else if (strcmp(method_str, "TRACE") == 0)      method = HTTP_METHOD_TRACE;
    else if (strcmp(method_str, "CONNECT") == 0)    method = HTTP_METHOD_CONNECT;
    else throw HttpException(HTTP_BAD_REQUEST, "Illformed request");
    
    // unsupported methods
    if ( !(method & HTTP_SUPPORTED_METHODS) )
        throw HttpException(HTTP_NOT_IMPLEMENTED, "Unsupported method");
    
    uri = uri_str;
    
    if (uri.find("..") != string::npos)
        throw HttpException(HTTP_FORBIDDEN, "Forbidden");
    
    valid = true;
    
    while (std::getline(is, line))
        parse(line);
}

HttpRequest::~HttpRequest()
{
}

const HttpMethod HttpRequest::getMethod() const
{
    return method;
}

const std::string& HttpRequest::getURI() const
{
    return uri;
}

std::string& HttpRequest::getValue(const std::string& key)
{
    return request[key];
}

void HttpRequest::parse(const std::string& line)
{
    string key, val;
    int pos = line.find(':');
    key = line.substr(0, pos);
    val = line.substr(pos+2, line.length());
    request[key] = val;
}

std::ostream& operator<<(std::ostream& os, const HttpRequest& request)
{
    return os << request.getMethod() << ' '
              << request.getURI() << " HTTP/"
              << ( request.getVersion() ).major << '.'
              << ( request.getVersion() ).minor;
}

