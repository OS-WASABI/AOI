# Get the base test environment image from Docker Hub
FROM oswasabi/aoi-test-env:latest

# Set the working directory
WORKDIR "/usr/src/aoi-rest-server"

# Copy the current folder which contains C++ source code to the Docker image under /usr/src
COPY "./src/" "./src/"
COPY CMakeLists.txt .

RUN mkdir build
WORKDIR "/usr/src/aoi-rest-server/build"

RUN cmake -G "Unix Makefiles" ..
RUN make

CMD ["./aoi-rest-server"]
