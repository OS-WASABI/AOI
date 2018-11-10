// Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
//                  Shawn Hulce, Michael McCulley
#include <iostream>
#include <string>
#include "another_controller.hpp"
#include "example_controller.hpp"
#include "user_controller.hpp"
#include "data_access_interface.hpp"
#include "data_access_object.hpp"
// The using statements allow me to not prepend each object with "aoi_rest::" each time I use them
using aoi_rest::DataAccessInterface;
using aoi_rest::DataAccessObject;
using aoi_rest::AnotherController;
using aoi_rest::ExampleController;
using aoi_rest::UserController;

int main(int argc, const char * argv[]) {
    std::cout << "Starting aoi rest server" << std::endl;
    // I use a pointer of the interface type to point to a reference of the DAO implementation
    // It's effectively casting in Java
    DataAccessInterface* user_dao = &DataAccessObject::Instance();
    AnotherController another_controller;
    ExampleController example_controller;
    // dereference the pointer, thereby passing the actual object 
    // and still treating it as the interface
    UserController user_controller(*user_dao);
    // create the server address string, if there were input arguments...
    std::string server_address;
    // The second argument is the host address
    if (argc > 2)
        server_address.append(argv[2]);
    // This host_auto_ip4 is some kind of voodoo magic that the network util class transforms into 
    // the servers outward facing ip address. Don't ask me how it works.
    else
        server_address.append("http://host_auto_ip4");
    // The first argument is the port number
    if (argc > 1)
        server_address.append(argv[1]);
    else
        server_address.append(":8080");
    server_address.append("/v1/aoi/api");
    another_controller.endpoint(server_address + "/another");
    example_controller.endpoint(server_address + "/example");
    user_controller.endpoint(server_address + "/users");
    try {
        // Accept returns a pplx::task
        // In other words, by calling wait on the task it will run async (non-blocking)
        // This is the magic that allows the controllers to respond to multiple calls.
        another_controller.Accept().wait();
        example_controller.Accept().wait();
        user_controller.Accept().wait();
        std::cout << "Listening for requests at: "
                << another_controller.endpoint() << std::endl
                << "Listening for requests at: "
                << example_controller.endpoint() << std::endl
                << "Listening for requests at: "
                << user_controller.endpoint() << std::endl;
        std::cout << "Press ENTER to exit." << std::endl;
        std::string line;
        std::getline(std::cin, line);
        another_controller.Shutdown().wait();
        example_controller.Shutdown().wait();
        user_controller.Shutdown().wait();
    }
    catch(std::exception&  e) {
        std::cerr << "There was an error" << std::endl;
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
