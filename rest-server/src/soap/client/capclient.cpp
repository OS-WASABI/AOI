#include "soapCAPSoapHttpProxy.h"
#include "CAPSoapHttp.nsmap"
#include <stdio.h>
#include <string>
#include <fstream>

const char server[] = "http://localhost:8080/aoi/soap/alerts";

// c++ -o capclient capclient.cpp stdsoap2.cpp soapC.cpp soapCAPSoapHttpProxy.cpp

int main(int argc, char **argv)
{
    if (argc < 3)
    {
        fprintf(stderr, "Usage: [send] filename \n");
        exit(0);
    }
    try {
        std::string filename = argv[2];
        _ns5__alert outboundAlert;
        struct soap ctx = *soap_new2(SOAP_XML_STRICT, SOAP_XML_INDENT);
        std::fstream fileIn(filename, std::fstream::in);

        ctx.is = &fileIn;

        soap_read__ns5__alert(&ctx, &outboundAlert);

        std::cout << "Sender Read: " << outboundAlert.sender << std::endl;

        CAPSoapHttpProxy cap;
        cap.soap_endpoint = server;
        _ns2__postCAPRequestTypeDef postRequest;   // request needs to contain data
        _ns2__postCAPResponseTypeDef response; // data holder for response

        postRequest.ns5__alert = &outboundAlert; // Assigns parsed alert to the request object
        postRequest.soap_serialize(&ctx); // Should serialize the alert for output? XML tags seem to have ns5: prefix

        cap.postCAP(&postRequest, response);

        if (cap.soap->error)
            cap.soap_stream_fault(std::cerr);
        else
            printf("result = %s\n", response.postCAPReturn);
            cap.destroy(); /* clean up mem */
        return 0;
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}
