# Alert Originator Interface REST Server

This is an open source solution that can be run on commodity hardware to allow alert originators to easily interface to FEMA IPAWS.

## Using Docker to Build and Test Locally
To run locally, first build the image.
```
docker build --rm -t aoi-rest-server .
```
Then run with the following command. The first port number is where your computer will be able to access endpoint.
```
docker run -d -it -p 8080:8080 aoi-rest-server
```
In postman or your browser, navigate to
```
http://localhost:8080/v1/aoi/api/service/test
```
And the response for a GET request will be
```
{
    "status": "ready!",
    "version": "0.1.1"
}
```