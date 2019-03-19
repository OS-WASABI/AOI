// Copyright 2019   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
//                  Shawn Hulce, Michael McCulley
/**
 * @file        cap.hpp
 * @authors     Ross Arcemont
 * @date        February, 2019
 */

#include <iostream>
#include <string>
#include <ctime>
#include "../pugixml-1.9/src/pugixml.hpp"
#include "../pugixml-1.9/src/pugixml.cpp"
#include "../../rest-server/src/model/alert.hpp"

#ifndef AOI_REST_SERVER_CAP_H
#define AOI_REST_SERVER_CAP_H

///Provides mechanisms through a static create_cap_doc method to create a CAP XML document using a provided CAP object
/**
 * Creates a syntactically correct SOAP CAP document using a pre-validated CAP object.
 * Example use: CAP::create_cap_doc(cap_object, "../file/path/to/save/capname.xml");
 */
class CAP {
public:
    ///Creates a CAP message from a provided CAP object.
    /**
     * Takes in a CAP object containing all necessary data to create a
     * CAP XML document. This function assumes that all necessary validation
     * of the CAP object data has occurred already, as this function does not
     * provide any such validation.
     * @param data_input        CAP object providing all necessary data
     * @param cap_filename      Filepath and filename of the CAP document to be saved
     */
    static std::string create_cap_doc(aoi_rest::Alert data_input);
};


#endif //AOI_REST_SERVER_CAP_H
