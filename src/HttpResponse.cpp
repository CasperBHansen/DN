/*
 * Datanet
 *
 * HttpResponse.cpp
 *
 */

#include "HttpResponse.h"

#define SERVER_NAME    "datanet"
#define SERVER_VERSION "1.0a"

#include <ctime>
#include <iostream>
#include <locale>

HttpResponse::HttpResponse(HttpResponseCode s)
            : status(s), content(""), mime_type("text/html"), serveContent(false)
{
}

HttpResponse::HttpResponse(HttpResponseCode s, std::string c, std::string mime)
            : status(s), content(c), mime_type(mime), serveContent(true)
{
}

HttpResponse::~HttpResponse()
{
}

HttpResponseCode HttpResponse::getStatus() const
{
    return status;
}

HttpResponse::operator std::string () const
{
    // get the date
    char date[64];
    std::time_t time = std::time(NULL);
    std::strftime(date, sizeof(date), "%a, %d %b %Y %H:%M:%S GMT", std::localtime(&time));
    
    std::ostringstream output;
    output << (* this) << std::endl
           << "Server: " << SERVER_NAME << '/' << SERVER_VERSION << std::endl
           << "Date: " << date << std::endl
           << "Content-Type: " << mime_type << std::endl
           << "Content-Length: " << content.length() << std::endl
           << "Connection: " << "close" << std::endl << std::endl;
    
    if (serveContent) output << content << std::endl << std::endl; 
    
    return output.str();
}

std::ostream& operator<<(std::ostream& stream, const HttpResponse& response)
{
    return stream << "HTTP/" << response.getVersion() << ' '
                             << response.getStatus() << ' '
                             << "SERVER MESSAGE";
}

void HttpResponse::stripContent()
{
    serveContent = false;
}

