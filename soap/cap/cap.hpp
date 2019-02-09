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
    static void create_cap_doc(aoi_rest::Alert data_input, std::string cap_filename);
};


#endif //AOI_REST_SERVER_CAP_H
