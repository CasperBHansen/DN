/*
 * Datanet
 *
 * HttpException.cpp
 *
 */

#include "HttpException.h"

HttpException::HttpException(HttpResponseCode status, std::string str)
             : code(status), msg(str)
{
}

HttpException::~HttpException()
{
}

const char * HttpException::what() throw()
{
    return msg.c_str();
}

const HttpResponseCode HttpException::which() throw()
{
    return code;
}

const std::string HttpException::html() throw()
{
    std::string content = "";
    content += "<html><head><title>Exception</title></head><body>";
    content += what();
    content += "</body></html>";
    return content;
}

