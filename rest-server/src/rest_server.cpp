// Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
//                  Shawn Hulce, Michael McCulley
#include <iostream>
#include <string>
#include "example_controller.hpp"
using aoi_rest::ExampleController;

int main(int argc, const char * argv[]) {
    std::cout << "Entering into main method." << std::endl;
    ExampleController server;
    utility::string_t server_address;
    if (argc > 2)
        server_address.append(argv[2]);
    else
        server_address.append("http://host_auto_ip4");
    if (argc > 1)
        server_address.append(argv[1]);
    else
        server_address.append(":8080");
    server_address.append("/v1/aoi/api");
    server.endpoint(server_address);
    try {
        server.Accept().wait();
        std::cout << "Listening for requests at: "
                << server.endpoint() << std::endl;
        std::cout << "Press ENTER to exit." << std::endl;
        std::string line;
        std::getline(std::cin, line);
        server.Shutdown().wait();
    }
    catch(std::exception&  e) {
        std::cerr << "There was an error" << std::endl;
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
