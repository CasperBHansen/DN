#include <iostream>
#include <string>

#include "ClientSocket.h"

int main (int argc, char * argv[])
{
    try
    {
        ClientSocket client_socket("localhost", 8080);

        std::string reply;

        try
        {
            client_socket << "GET /file.txt HTTP/1.1";
            client_socket >> reply;
        }
        catch (SocketException& e) {}

        std::cout << "We received this response from the server:\n\"" << reply << "\"\n";;

    }
    catch (SocketException& e)
    {
        std::cout << "Exception was caught:" << e.what() << "\n";
    }

    return 0;
}

