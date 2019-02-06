//
// Created by Ross on 1/31/2019.
//

#include <iostream>
#include <string>
#include <ctime>
#include "../pugixml-1.9/src/pugixml.hpp"
#include "../pugixml-1.9/src/pugixml.cpp"
#include "../../rest-server/src/model/alert.hpp"

#ifndef AOI_REST_SERVER_CAP_H
#define AOI_REST_SERVER_CAP_H


class CAP {
public:
    CAP();
    void create_cap_doc(aoi_rest::Alert data_input, std::string cap_filename);

private:
    pugi::xml_document cap_doc;
    auto declaration_node = cap_doc.append_child(pugi::node_declaration);
    auto root_node = cap_doc.append_child("SOAP-ENV:Envelope");
    auto soap_body = root_node.append_child("SOAP-ENV:Body");

    auto alert = soap_body.append_child("alert");
    auto identifier = alert.append_child("identifier");
    auto sender = alert.append_child("sent");
    auto sent = alert.append_child("sent");
    auto status = alert.append_child("status");
    auto msg_type = alert.append_child("msgType");
    auto source = alert.append_child("source");
    auto scope = alert.append_child("scope");
    auto restriction = alert.append_child("restriction");
    auto addresses = alert.append_child("addresses");

    auto note = alert.append_child("note");
    auto references = alert.append_child("references");
    auto incidents = alert.append_child("incidents");






};


#endif //AOI_REST_SERVER_CAP_H
