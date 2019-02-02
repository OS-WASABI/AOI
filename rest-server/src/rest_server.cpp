// Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
//                  Shawn Hulce, Michael McCulley
#include <iostream>
#include <string>
#include "data_access_interface.hpp"
#include "data_access_object.hpp"
#include "logger.hpp"
#include "log_level.hpp"
#include "./soap/controller/soap_controller.hpp"
using aoi_rest::DataAccessInterface;
using aoi_rest::DataAccessObject;
using aoi_rest::Logger;
using aoi_rest::LoggerInterface;
using aoi_soap::SoapController;

int main(int argc, const char * argv[]) {
    LoggerInterface& logger(Logger::Instance());
    std::cout << "Starting aoi rest server" << std::endl;
    SoapController soap_controller(DataAccessObject::Instance());
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
    soap_controller.endpoint("http://host_auto_ip4:8080/aoi/soap/alerts");
    try {
        soap_controller.Accept().wait();
        std::cout << "Listening for requests at: "
                << soap_controller.endpoint() << std::endl
                << "Listening for requests at: "
                << std::endl;
        std::cout << "Press ENTER to exit." << std::endl;
        std::string line;
        std::getline(std::cin, line);
        soap_controller.Shutdown().wait();
    }
    catch(std::exception&  e) {
        std::cerr << "There was an error" << std::endl;
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
