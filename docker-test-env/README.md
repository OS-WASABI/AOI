# Travis Test - AOI Build and Test Environment Base Image Docker File

If the base image needs to be adjusted, this is the Dockerfile that generates it. Leave off `my-tag` to update the latest version for production.

Build simply with 
```
docker build -t aoi-test-env:my-tag .
```

To push image to DockerHub
```
$ docker tag aoi-test-env:my-tag oswasabi/aoi-test-env:my-tag

$ docker push oswasabi/aoi-test-env:my-tag
```