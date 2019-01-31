//
// Created by Ross on 1/31/2019.
//

#include "cap.hpp"

CAP::CAP() {
    //TODO: Verify this information
    //Default node attributes
    declaration_node.append_attribute("version") = "1.0";
    declaration_node.append_attribute("encoding") = "utf-8";
    root_node.append_attribute("xmlns:SOAP-ENV") = "\"http://www.w3.org/2001/12/soap-envelope\"";
    root_node.append_attribute("SOAP-ENV:encodingStyle") = "\"http://www.w3.org/2001/12/soap-encoding\"";
    alert.append_attribute("xmlns") = "\"urn:oasis:names:tc:emergency:cap:1.2\"";
}