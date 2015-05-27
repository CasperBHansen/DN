/*
 * Datanet
 *
 * HttpMessage.h
 *
 */

#ifndef HTTPMESSAGE_H
#define HTTPMESSAGE_H

#include <iostream>

#include "HttpException.h"

struct HttpVersion {
    int major, minor;
};

std::ostream& operator<<(std::ostream& stream, const HttpVersion& version);

class HttpMessage
{
public:
	HttpMessage();
	~HttpMessage();
    
    const HttpVersion& getVersion() const;
    
    bool isValid() const;
    
protected:
    HttpVersion version;
    
    bool valid;
    
private:
};

#endif // HTTPMESSAGE_H

