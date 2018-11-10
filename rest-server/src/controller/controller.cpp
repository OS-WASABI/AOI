// Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
//                  Shawn Hulce, Michael McCulley
#include <pplx/pplxtasks.h>
#include <controller.hpp>
#include <map>
#include <string>
#include <vector>
#include "network_utils.hpp"

namespace aoi_rest {
// The base controller is effectively a Java abstract class.
// It contains some implementation for things all controllers need, but leaves several methods undefined.
Controller::Controller() {}
Controller::~Controller() {}
void Controller::endpoint(const std::string& value) {
    uri endpointURI(value);
    uri_builder endpointBuilder;
    endpointBuilder.set_scheme(endpointURI.scheme());
    if (endpointURI.host() == "host_auto_ip4")
        endpointBuilder.set_host(NetworkUtils::hostIP4());
    else if (endpointURI.host() == "host_auto_ip6")
        endpointBuilder.set_host(NetworkUtils::hostIP6());
    endpointBuilder.set_port(endpointURI.port());
    endpointBuilder.set_path(endpointURI.path());
    listener__ = http_listener(endpointBuilder.to_uri());
}
std::string Controller::endpoint() const {
    return listener__.uri().to_string();
}
pplx::task<void> Controller::Accept() {
    InitHandlers();
    return listener__.open();
}
pplx::task<void> Controller::Shutdown() {
    return listener__.close();
}
std::vector<std::string> Controller::RequestPath(const http_request& message) {
    auto relative_path = uri::decode(message.relative_uri().path());
    return uri::split_path(relative_path);
}
// I needed to create a method for parsing the query string.
// Since all controllers may need this functionality, I put it in the base class
// This implementation is not perfect and there are several things it doesn't take into consideration.
// Effectively it implements a string split method
std::map<std::string, std::string> Controller::Queries(std::string query_string) {
    std::map<std::string, std::string> query_map;
    std::string query_delimeter = "&";  // technically, it could be delimited by ';' too
    std::string value_delimeter = "=";
    // This is the main string split loop
    for (int begining_position = 0, ending_position = 0;
                ending_position < query_string.length() && begining_position < query_string.length();
                begining_position = ending_position + query_delimeter.length()) {
        ending_position = query_string.find(query_delimeter, begining_position);
        if (ending_position == std::string::npos)  // found the end of the query string
            ending_position = query_string.length();
        std::string token = query_string.substr(begining_position, ending_position - begining_position);
        // if there is a new token, it will try to parse it into a key and value by finding a '='
        if (!token.empty()) {
            int name_value_split = token.find(value_delimeter, 0);
            if (name_value_split != std::string::npos) {
                std::string name = token.substr(0, name_value_split);
                std::string value = token.substr(name_value_split + value_delimeter.length());
                query_map[name] = value;
            }
        }
    }
    return query_map;
}
json::value Controller::ResponseNotImpl(const http::method & method) {
    auto response = json::value::object();
    response["http_method"] = json::value::string(method);
    response["serviceName"] = json::value::string("AOI Service");
    return response;
}
}  // namespace aoi_rest
