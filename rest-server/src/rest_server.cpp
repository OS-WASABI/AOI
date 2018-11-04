// Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
//                  Shawn Hulce, Michael McCulley
#include <iostream>
#include <string>
#include "example_controller.hpp"
#include "another_controller.hpp"
using aoi_rest::ExampleController;
using aoi_rest::AnotherController;

int main(int argc, const char * argv[]) {
    std::cout << "Starting aoi rest server" << std::endl;
    ExampleController example_controller;
    AnotherController another_controller;
    std::string server_address;
    if (argc > 2)
        server_address.append(argv[2]);
    else
        server_address.append("http://host_auto_ip4");
    if (argc > 1)
        server_address.append(argv[1]);
    else
        server_address.append(":8080");
    server_address.append("/v1/aoi/api");
    example_controller.endpoint(server_address + "/example");
    another_controller.endpoint(server_address + "/another");
    try {
        example_controller.Accept().wait();
        another_controller.Accept().wait();
        std::cout << "Listening for requests at: "
                << example_controller.endpoint() << std::endl
                << "Listening for requests at: "
                << another_controller.endpoint() << std::endl;
        std::cout << "Press ENTER to exit." << std::endl;
        std::string line;
        std::getline(std::cin, line);
        example_controller.Shutdown().wait();
        another_controller.Shutdown().wait();
    }
    catch(std::exception&  e) {
        std::cerr << "There was an error" << std::endl;
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
