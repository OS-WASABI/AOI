#include "soapCAPSoapHttpProxy.h"
#include "CAPSoapHttp.nsmap"

const char server[] = "http://localhost:8210";

// c++ -o capclient capclient.cpp stdsoap2.cpp soapC.cpp soapCAPSoapHttpProxy.cpp

int main(int argc, char **argv)
{
    if (argc < 3)
    {
        fprintf(stderr, "Usage: [send] filename \n");
        exit(0);
    }
    std::string filename = argv[3];
    // CAPSoapHttpProxy cap;
    // cap.soap_endpoint = server;
    // _ns1__postCAPRequestTypeDef ns1__postCAPRequestTypeDef;   // request needs to contain data
    // _ns1__postCAPResponseTypeDef ns1__postCAPResponseTypeDef; // data holder for response
    // cap.postCAP(&ns1__postCAPRequestTypeDef, ns1__postCAPResponseTypeDef);

    // if (cap.soap->error)
    //     cap.soap_stream_fault(std::cerr);
    // else
        // printf("result = %s\n", ns1__postCAPResponseTypeDef.postCAPReturn);
    // cap.destroy(); /* clean up mem */
    return 0;
}
