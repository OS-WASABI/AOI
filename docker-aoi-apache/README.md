# AOI Apache Docker Image

This utilizes version 2.4 of the Apache httpd server. The configuration file is extremely basic at present and will need to be built. As such, this has been tagged as prototype for the time being.

To build locally
```
docker build -t aoi-apache:prototype .
```
Note: Replace tag with your desired nomenclature. Also note that you can pull the current prototype image from the docker hub with:
```
docker pull os-wasabi/aoi-apache:prototype
```

Run Directions:
To run this container you will need to provide it port information as well as a name. As below:
```
docker run -d --name aoi-apache -p 8080:80 aoi-apache:prototype
```