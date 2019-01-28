### This script automates setting up a
### Build and Test Environment on Ubuntu 18.04 for AOI

# Add ubuntu toolchain repository
apt-get -q -d update
apt-get install -q -y software-properties-common
add-apt-repository -y ppa:ubuntu-toolchain-r/test
apt-get -q -d update

# Install tools
apt-get -q -y install \
    cmake \
    cppcheck \
    doxygen \
    g++-8 \
    libasio-dev \
    libcpprest-dev \
    libspdlog-dev \
    nano \
    software-properties-common \
    unixodbc-dev \
    vim \
    wget

# Make g++ 8 the default g++ executable
update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-8 90

# Google Fruit dependency injection, build install remove old files
cd /usr/src &&\
    mkdir gfruit &&\
    cd gfruit &&\
    wget https://github.com/google/fruit/archive/v3.4.0.tar.gz &&\
    tar -xvzf v3.4.0.tar.gz &&\
    cd fruit-3.4.0 &&\
    cmake -DCMAKE_BUILD_TYPE=Release -DFRUIT_USES_BOOST=False . && make -j &&\
    make install &&\
    ldconfig

# Get gtest libraries, compile, move to lib folder, cleanup
cd /usr/src &&\
    apt-get install libgtest-dev -y -q &&\
    cd /usr/src/gtest &&\
    cmake CMakeLists.txt &&\
    make &&\
    cp *.a /usr/lib &&\
    cd .. &&\
    rm -R gtest

# Download and install MySQL8 odbc
cd /usr/src &&\
    wget https://dev.mysql.com/get/Downloads/Connector-ODBC/8.0/mysql-connector-odbc-8.0.13-linux-ubuntu18.04-x86-64bit.tar.gz &&\
    gunzip mysql-connector-odbc-8.0.13-linux-ubuntu18.04-x86-64bit.tar.gz && \
    tar xvf mysql-connector-odbc-8.0.13-linux-ubuntu18.04-x86-64bit.tar &&\
    cp mysql-connector-odbc-8.0.13-linux-ubuntu18.04-x86-64bit/bin/* /usr/local/bin &&\
    cp mysql-connector-odbc-8.0.13-linux-ubuntu18.04-x86-64bit/lib/* /usr/local/lib &&\
    myodbc-installer -a -d -n "MySQL8Driver" -t "Driver=/usr/local/lib/libmyodbc8w.so" &&\
    myodbc-installer -a -d -n "MySQL8" -t "Driver=/usr/local/lib/libmyodbc8a.so"

# Download cpplint.py and set the file permissions so that it is executable
cd /usr/src &&\
    mkdir aoi &&\
    cd aoi &&\
    wget https://raw.githubusercontent.com/google/styleguide/gh-pages/cpplint/cpplint.py &&\
    chmod +x cpplint.py
