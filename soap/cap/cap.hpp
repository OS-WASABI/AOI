//
// Created by Ross on 1/31/2019.
//

#include <iostream>
#include <string>
#include <ctime>
#include "../pugixml-1.9/src/pugixml.hpp"
#include "../pugixml-1.9/src/pugixml.cpp"

#ifndef AOI_REST_SERVER_CAP_H
#define AOI_REST_SERVER_CAP_H


class CAP {
public:
    CAP();
    void create_cap_doc(std::string data_input, std::string cap_filename);

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
    auto code = alert.append_child("code"); //TODO: Allow for multiple codes
    auto note = alert.append_child("note");
    auto references = alert.append_child("references");
    auto incidents = alert.append_child("incidents");

    auto info = alert.append_child("info"); //TODO: Allow for multiple info blocks
    auto language = info.append_child("language");
    auto category = info.append_child("category"); //TODO: Allow for multiple categories
    auto event = info.append_child("event");
    auto response_type = info.append_child("responseType"); //TODO: Allow for multiple response types
    auto urgency = info.append_child("urgency");
    auto severity = info.append_child("severity");
    auto certainty = info.append_child("certainty");
    auto audience = info.append_child("audience");
    auto event_code = info.append_child("eventCode"); //TODO: Allow for multiple event codes
    auto effective = info.append_child("effective");
    auto onset = info.append_child("onset");
    auto expires = info.append_child("expires");
    auto sender_name = info.append_child("senderName");
    auto headline = info.append_child("headline");
    auto description = info.append_child("description");
    auto instruction = info.append_child("instruction");
    auto web = info.append_child("web");
    auto contact = info.append_child("contact");
    auto parameter = info.append_child("parameter"); //TODO: Allow for multiple parameters

    auto resource = info.append_child("resource"); //TODO: Allow for multiple resource blocks
    auto resource_desc = resource.append_child("resourceDesc");
    auto mime_type = resource.append_child("mimeType");
    auto size = resource.append_child("size");
    auto uri = resource.append_child("uri");
    auto dereferenced_uri = resource.append_child("derefUri");
    auto digest = resource.append_child("digest");

    auto area = info.append_child("area"); //TODO: Allow for multiple area blocks
    auto area_desc = area.append_child("areaDesc");
    auto polygon = area.append_child("polygon"); //TODO: Allow for multiple polygons
    auto circle = area.append_child("circle"); //TODO: Allow for multiple circles
    auto geocode = area.append_child("geocode"); //TODO: Allow for multiple geocodes
    auto altitude = area.append_child("altitude");
    auto ceiling = area.append_child("ceiling");
};


#endif //AOI_REST_SERVER_CAP_H
