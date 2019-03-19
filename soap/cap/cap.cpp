// Copyright 2019   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
//                  Shawn Hulce, Michael McCulley
/**
 * @file        cap.cpp
 * @authors     Ross Arcemont
 * @date        February, 2019
 */

#include "cap.hpp"
#include <sstream>

///Creates a CAP message from a provided CAP object.
/**
 * Takes in a CAP object containing all necessary data to create a
 * CAP XML document. This function assumes that all necessary validation
 * of the CAP object data has occurred already, as this function does not
 * provide any such validation.
 * @param data_input        CAP object providing all necessary data
 * @param cap_filename      Filepath and filename of the CAP document to be saved
 */
std::string CAP::create_cap_doc(aoi_rest::Alert data_input) {
    pugi::xml_document cap_doc;
    pugi::xml_node declaration_node = cap_doc.append_child(pugi::node_declaration);
    declaration_node.append_attribute("version") = "1.0";
    declaration_node.append_attribute("encoding") = "utf-8";

    // Creating SOAP envelope for the CAP message
//    pugi::xml_node root_node = cap_doc.append_child("SOAP-ENV:Envelope");
//    root_node.append_attribute("xmlns:SOAP-ENV") = "http://www.w3.org/2001/12/soap-envelope";
//    root_node.append_attribute("SOAP-ENV:encodingStyle") = "http://www.w3.org/2001/12/soap-encoding";
//
//    pugi::xml_node soap_body = root_node.append_child("SOAP-ENV:Body");

    // Creating CAP message main structure with necessary data
    pugi::xml_node alert = cap_doc.append_child("alert");
    alert.append_attribute("xmlns") = "urn:oasis:names:tc:emergency:cap:1.2";

    pugi::xml_node identifier = alert.append_child("identifier");
    identifier.text().set(data_input.identifier.value().c_str());

    pugi::xml_node sender = alert.append_child("sender");
    sender.text().set(data_input.sender.value().c_str());

    pugi::xml_node sent = alert.append_child("sent");
    sent.text().set(data_input.sent_time.value().c_str());

    pugi::xml_node status = alert.append_child("status");
    status.text().set(data_input.status.value().c_str());

    pugi::xml_node msg_type = alert.append_child("msgType");
    msg_type.text().set(data_input.msg_type.value().c_str());

    if (data_input.source) {
        pugi::xml_node source = alert.append_child("source");
        source.text().set(data_input.source.value().c_str());
    }

    pugi::xml_node scope = alert.append_child("scope");
    scope.text().set(data_input.scope.value().c_str());

    if (data_input.restriction) {
        pugi::xml_node restriction = alert.append_child("restriction");
        restriction.text().set(data_input.restriction.value().c_str());
    }

    if (data_input.addresses) {
        pugi::xml_node addresses = alert.append_child("addresses");
        addresses.text().set(data_input.addresses.value().c_str());
    }

    if (data_input.handling_codes) {
        for (int i = 0; i < data_input.handling_codes.value().size(); i++) {
            pugi::xml_node code = alert.append_child("code");
            code.text().set(data_input.handling_codes.value().at(i).c_str());
        }
    }

    if (data_input.note) {
        pugi::xml_node note = alert.append_child("note");
        note.text().set(data_input.note.value().c_str());
    }

    if (data_input.references) {
        pugi::xml_node references = alert.append_child("references");
        references.text().set(data_input.references.value().c_str());
    }

    if (data_input.incidents) {
        pugi::xml_node incidents = alert.append_child("incidents");
        incidents.text().set(data_input.incidents.value().c_str());
    }

    // Creating info blocks with necessary data
    if (data_input.info) {
        for (int i = 0; i < data_input.info.value().size(); i++) {
            pugi::xml_node info = alert.append_child("info");
            pugi::xml_node language = info.append_child("language");
            if (data_input.info.value().at(i).language) {
                language.text().set(data_input.info.value().at(i).language.value().c_str());
            }

            for (int j = 0; j < data_input.info.value().at(i).categories.value().size(); j++) {
                pugi::xml_node category = info.append_child("category");
                category.text().set(data_input.info.value().at(i).categories.at(j).value().c_str());
            }

            pugi::xml_node event = info.append_child("event");
            event.text().set(data_input.info.value().at(i).event.value().c_str());

            if (data_input.info.value().at(i).response_types) {
                for (int j = 0; j < data_input.info.value().at(i).response_types.value().size(); j++) {
                    pugi::xml_node response_type = info.append_child("responseType");
                    response_type.text().set(data_input.info.value().at(i).response_types.value().at(j).c_str());
                }
            }

            pugi::xml_node urgency = info.append_child("urgency");
            urgency.text().set(data_input.info.value().at(i).urgency.value().c_str());

            pugi::xml_node severity = info.append_child("severity");
            severity.text().set(data_input.info.value().at(i).severity.value().c_str());

            pugi::xml_node certainty = info.append_child("certainty");
            certainty.text().set(data_input.info.value().at(i).certainty.value().c_str());

            if (data_input.info.value().at(i).audience) {
                pugi::xml_node audience = info.append_child("audience");
                audience.text().set(data_input.info.value().at(i).audience.value().c_str());
            }

            if (data_input.info.value().at(i).event_codes) {
                for (int j = 0; j < data_input.info.value().at(i).event_codes.value().size(); j++) {
                    pugi::xml_node event_code = info.append_child("eventCode");
                    pugi::xml_node value_name = event_code.append_child("valueName");
                    pugi::xml_node value = event_code.append_child("value");

                    value_name.text().set(data_input.info.value().at(i).event_codes.value().at(j).first.c_str());
                    value.text().set(data_input.info.value().at(i).event_codes.value().at(j).second.c_str());
                }
            }

            if (data_input.info.value().at(i).effective) {
                pugi::xml_node effective = info.append_child("effective");
                effective.text().set(data_input.info.value().at(i).effective_time.value().c_str());
            }

            if (data_input.info.value().at(i).onset) {
                pugi::xml_node onset = info.append_child("onset");
                onset.text().set(data_input.info.value().at(i).onset_time.value().c_str());
            }

            if (data_input.info.value().at(i).expires) {
                pugi::xml_node expires = info.append_child("expires");
                expires.text().set(data_input.info.value().at(i).expire_time.value().c_str());
            }

            if (data_input.info.value().at(i).sender_name) {
                pugi::xml_node sender_name = info.append_child("senderName");
                sender_name.text().set(data_input.info.value().at(i).sender_name.value().c_str());
            }

            if (data_input.info.value().at(i).headline) {
                pugi::xml_node headline = info.append_child("headline");
                headline.text().set(data_input.info.value().at(i).headline.value().c_str());
            }

            if (data_input.info.value().at(i).description) {
                pugi::xml_node description = info.append_child("description");
                description.text().set(data_input.info.value().at(i).description.value().c_str());
            }

            if (data_input.info.value().at(i).instruction) {
                pugi::xml_node instruction = info.append_child("instruction");
                instruction.text().set(data_input.info.value().at(i).instruction.value().c_str());
            }

            if (data_input.info.value().at(i).web_url) {
                pugi::xml_node web = info.append_child("web");
                web.text().set(data_input.info.value().at(i).web_url.value().c_str());
            }

            if (data_input.info.value().at(i).contact) {
                pugi::xml_node contact = info.append_child("contact");
                contact.text().set(data_input.info.value.at(i).contact.value().c_str());
            }

            if (data_input.info.value().at(i).parameters)
            for (int j = 0; j < data_input.info.at(i).parameters.size(); j++) {
                pugi::xml_node parameter = info.append_child("parameter");
                parameter.text().set(data_input.info.value().at(i).parameters.value().at(j).c_str());
            }

            // Creating resource blocks with necessary data
            if (data_input.info.value().at(i).resources) {
                for (int j = 0; j < data_input.info.value().at(i).resources.size(); j++) {
                    pugi::xml_node resource = info.append_child("resource");
                    pugi::xml_node resource_desc = resource.append_child("resourceDesc");
                    resource_desc.text().set(data_input.info.value().at(i).resources.value().at(j)
                    .resource_description.value().c_str());

                    pugi::xml_node mime_type = resource.append_child("mimeType");
                    mime_type.text().set(data_input.info.value().at(i).resources.value().at(j)
                    .mime_type.value().c_str());

                    if (data_input.info.value().at(i).resources.value().at(j).size) {
                        pugi::xml_node size = resource.append_child("size");
                        size.text().set(data_input.info.value().at(i).resources.value().at(j).size.value().c_str());
                    }

                    if (data_input.info.value().at(i).resources.value().at(j).uri) {
                        pugi::xml_node uri = resource.append_child("uri");
                        uri.text().set(data_input.info.value().at(i).resources.value().at(j).uri.value().c_str());
                    }

                    if (data_input.info.value().at(i).resources.value().at(j).dereferenced_uri) {
                        pugi::xml_node dereferenced_uri = resource.append_child("derefUri");
                        dereferenced_uri.text().set(data_input.info.value().at(i).resources.value().at(j)
                        .dereferenced_uri.value().c_str());
                    }

                    if (data_input.info.value().at(i).resources.value().at(j).digest) {
                        pugi::xml_node digest = resource.append_child("digest");
                        digest.text().set(data_input.info.value().at(i).resources.value().at(j)
                        .digest.value().c_str());
                    }
                }
            }

            // Creating area blocks with necessary data
            if (data_input.info.value().at(i).areas) {
                for (int j = 0; j < data_input.info.value().at(i).areas.value().size(); j++) {
                    pugi::xml_node area = info.append_child("area");
                    pugi::xml_node area_desc = area.append_child("areaDesc");
                    area_desc.text().set(data_input.info.value().at(i).areas.value().at(j)
                    .area_description.value().c_str());

                    if (data_input.info.value().at(i).areas.value().at(j).polygons) {
                        for (int k = 0; k < data_input.info.value().at(i).areas.value().at(j)
                        .polygons.value().size(); k++) {
                            pugi::xml_node polygon = area.append_child("polygon");
                            polygon.text().set(data_input.info.value().at(i).areas.value().at(j)
                            .polygons.value().at(k).c_str());
                        }
                    }

                    if (data_input.info.value().at(i).areas.value().at(j).circles) {
                        for (int k = 0; k < data_input.info.value().at(i).areas.value().at(j)
                        .circles.value().size(); k++) {
                            pugi::xml_node circle = area.append_child("circle");
                            circle.text().set(data_input.info.value().at(i).areas.value().at(j)
                            .circles.value().at(k).c_str());
                        }
                    }

                    if (data_input.info.value().at(i).areas.value().at(j).geocode) {
                        for (int k = 0; k < data_input.info.at(i).areas.at(j).geocode.size(); k++) {
                            pugi::xml_node geocode = area.append_child("geocode");
                            pugi::xml_node value_name = geocode.append_child("valueName");
                            pugi::xml_node value = geocode.append_child("value");

                            value_name.text().set(data_input.info.value().at(i).areas.value().at(j)
                            .geocode.value().at(k).first.c_str());
                            value.text().set(data_input.info.value().at(i).areas.value().at(j)
                            .geocode.value().at(k).second.c_str());
                        }
                    }

                    if (data_input.info.value().at(i).areas.value().at(j).altitude) {
                        pugi::xml_node altitude = area.append_child("altitude");
                        altitude.text().set(data_input.info.value().at(i).areas.value().at(j)
                        .altitude.value().c_str());
                    }

                    if (data_input.info.value().at(i).areas.value().at(j).ceiling) {
                        pugi::xml_node ceiling = area.append_child("ceiling");
                        ceiling.text().set(data_input.info.value().at(i).areas.value().at(j).ceiling.value().c_str());
                    }
                }
            }
        }
    }

    // Saving the CAP message as the final string output
    std::stringstream cap_xml_stream;
    cap_doc.save(cap_xml_stream);
    std::string cap_xml_string = cap_xml_stream.str();
    return cap_xml_string;
}

int main() {
    aoi_rest::Alert test_alert;
    test_alert.identifier = "9001";
    test_alert.sender = "Ross";
    test_alert.sent_time = "2019-03-28T19:54-9:00";
    test_alert.status = "Actual";
    test_alert.msg_type = "Alert";
    test_alert.source = "CDC";
    test_alert.scope = "Public";
}
