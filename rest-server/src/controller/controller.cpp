// Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
//                  Shawn Hulce, Michael McCulley
#include <pplx/pplxtasks.h>
#include <controller.hpp>
#include <string>
#include <vector>
#include "network_utils.hpp"

namespace aoi_rest {
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
json::value Controller::ResponseNotImpl(const http::method & method) {
    auto response = json::value::object();
    response["http_method"] = json::value::string(method);
    response["serviceName"] = json::value::string("AOI Service");
    return response;
}
}  // namespace aoi_rest
