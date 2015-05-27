/*
 * Datanet
 *
 * HttpResponse.h
 *
 */

#ifndef HTTPRESPONSE_H
#define HTTPRESPONSE_H

#include <sstream>
#include <string>

#include "HttpMessage.h"

class HttpResponse : public HttpMessage
{
public:
	HttpResponse(HttpResponseCode status = HTTP_NOT_IMPLEMENTED);
	HttpResponse(HttpResponseCode status, std::string content, std::string mime = "text/html");
	~HttpResponse();
    
    HttpResponseCode getStatus() const;
    
    operator std::string () const;
    
    void stripContent();
    
protected:
private:
    HttpResponseCode status;
    
    // content
    std::string content;
    std::string mime_type;
    
    bool serveContent;
};

std::ostream& operator<<(std::ostream& stream, const HttpResponse& response);

#endif // HTTPRESPONSE_H

