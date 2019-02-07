#include "soapCAPSoapHttpProxy.h"
#include "CAPSoapHttp.nsmap"
#include <stdio.h>

const char server[] = "http://localhost:8080/aoi/soap/alerts";

// c++ -o capclient capclient.cpp stdsoap2.cpp soapC.cpp soapCAPSoapHttpProxy.cpp

int main(int argc, char **argv)
{
    if (argc < 3)
    {
        fprintf(stderr, "Usage: [send] filename \n");
        exit(0);
    }
    std::string filename = argv[3];
    struct soap
    _ns2__alert outboundAlert;
    struct soap ctx = *soap_new2(SOAP_XML_STRICT, SOAP_XML_INDENT);
    std::ifstream fileIn("./alert1", std::ifstream::in);

    //ctx.is = &fileIn;

    //soap_read__ns2__alert(&ctx, &outboundAlert);

    //std::cout << "Sender Read: " << outboundAlert.sender << std::endl;

    CAPSoapHttpProxy cap;
    cap.soap_endpoint = server;
    _ns2__postCAPRequestTypeDef postRequest;   // request needs to contain data
    _ns2__postCAPResponseTypeDef response; // data holder for response
    
    cap.send_postCAP(server, *SOAP_POST, postRequest);

    //cap.postCAP(&ns1__postCAPRequestTypeDef, ns1__postCAPResponseTypeDef);
    if (cap.soap->error)
         cap.soap_stream_fault(std::cerr);
     else
         printf("result = %s\n", ns1__postCAPResponseTypeDef.postCAPReturn);
     cap.destroy(); /* clean up mem */
    return 0;
}
