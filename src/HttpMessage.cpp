/*
 * Datanet
 *
 * HttpMessage.cpp
 *
 */

#include "HttpMessage.h"

std::ostream& operator<<(std::ostream& stream, const HttpVersion& version)
{
    return stream << version.major << '.' << version.minor;
}


const HttpVersion server_version = { 1, 0 };

HttpMessage::HttpMessage()
           : version(server_version), valid(false)
{
}

HttpMessage::~HttpMessage()
{
    valid = false;
}

const HttpVersion& HttpMessage::getVersion() const
{
    return version;
}

bool HttpMessage::isValid() const
{
    return valid;
}

