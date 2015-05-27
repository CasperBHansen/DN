#include <iostream>
#include <string>

#include "ServerSocket.h"

int main (int argc, char * argv[])
{
    std::cout << "running....\n";

    try
    {
        // Create the socket
        ServerSocket server(30000);

        while (true)
        {

            ServerSocket socket;
            server.accept(socket);

            try
            {
                while ( true )
                {
                    std::string data;
                    socket >> data;
                    std::cout << "Server received message (" << data.length() << "):\n" << data << std::endl;
                    socket << data;
                }
            }
            catch (SocketException& e) {}

        }
    }
    catch (SocketException& e)
    {
        std::cout << "Exception was caught:" << e.what() << "\nExiting.\n";
    }

    return 0;
}

