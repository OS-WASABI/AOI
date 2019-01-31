Steps I took to run the calc gSOAP example. You will want to start from an empty directory like I did. I included the resulting files for example only.

# Installation
Linux download/install directions [https://www.genivia.com/downloads.html#unix](https://www.genivia.com/downloads.html#unix)
1. Install flex/bison
```
sudo apt-get install flex bison
```
2. Install OpenSSL
```
sudo apt-get install libssl-dev
```
3. Download zip from [https://sourceforge.net/projects/gsoap2/](https://sourceforge.net/projects/gsoap2/)

4. Configure the installation with flags
I had an issue with an [undefined reference to pthread](https://sourceforge.net/p/gsoap2/bugs/481/)
```
./configure LDFLAGS=-pthread 
```
4. Make
```
make
```
5. Install
```
sudo make install exec_prefix=$HOME
```

# Calc Client
Example instructions located here [https://www.genivia.com/examples/calc++/index.html](https://www.genivia.com/examples/calc++/index.html)
NOTE: Don't use the provided code, if the version of gSOAP that generates the code is different than what you have installed it won't build.
1. To generate from the WSDL
```
wsdl2h -o calc.h http://www.genivia.com/calc.wsdl
```
2. Follow the directions to "bind XML namespace prefixes to namespace URIs that wsdl2h will use. 
Since this service uses URI "urn:calc" and we want this to be bound to the ns prefix we should add the following line to [typemap.dat](https://www.genivia.com/examples/calc++/typemap.dat)"
```
ns2 = "http://websrv.cs.fsu.edu/~engelen/calc.wsdl"
ns = "urn:calc"
```
3. Run the WSDL again
```
wsdl2h -o calc.h http://www.genivia.com/calc.wsdl
```
4. You need the implementation of the [calcclient.cpp](https://www.genivia.com/examples/calc++/calcclient.cpp) in the directory.
5. You also need `stdsoap2.cpp` and `stdsoap.h` which are in the gsoap installation. For me, it was located at
```
/gsoap_2.8.78/gsoap-2.8/gsoap/stdsoap2.cpp
/gsoap_2.8.78/gsoap-2.8/gsoap/stdsoap2.h
```
6. Generate files from the calc.h
```
soapcpp2 -j -r -CL calc.h
```
7. Build the application
```
c++ -o calcclient calcclient.cpp stdsoap2.cpp soapC.cpp soapcalcProxy.cpp
```
# Calc Server
1. If starting in a new directory, you will need the following files from the client
```
calc.h
stdsoap.h
stdsoap.cpp
```
2. Add the example calcserver.cpp file [calcserver.cpp](https://www.genivia.com/examples/calc++/calcserver.cpp)

3. Change lines 91 and 103 to the following
```
    char *s = (char*)soap_malloc(this->soap, 1024);
```
4. Generate files
```
soapcpp2 -j -r -SL calc.h
```
5. Build
```
c++ -o calcserver calcserver.cpp stdsoap2.cpp soapC.cpp soapcalcService.cpp
```

# Running the Server/Client
1. If running on localhost, change line 44 of calcclient.cpp to
```
const char server[] =  "http://localhost:8080";
```
2. Run the server, passing in the appropriate port number
```
./calcserver 8080
```
3. Make SOAP calls by running the client with appropriate args
```
./calcclient add 2 3
```