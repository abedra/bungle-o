## This project is no longer in active development

# bungle-o

bungle-o is a data capturing service built on top of zeromq, tofu, and redis. It uses the redis push/pull model with an http endpoint as the front end. The current focus is creating a hoptoad/airbrake style capturing endpoint. The compatability with hoptoad/airbrake messages is still in the works, but the foundation is all present. Later, the goal will be to open the capturing up to other things like logging, metrics reporting etc., to enable a one stop place for capturing data inside your infrastructure. While you only start one bungelo server, you can have as many clients as your heart desires to handle processing all of the messages that come in.

## Dependencies

jansson

    wget http://www.digip.org/jansson/releases/jansson-2.2.1.tar.gz
    tar xvzf jansson-2.2.1.tar.gz
    cd janson-2.2.1
    ./configure
    make
    sudo make install

libevent
    
    wget https://github.com/downloads/libevent/libevent/libevent-2.0.16-stable.tar.gz
    tar xvzf libevent-2.0.16-stable
    ./configure
    make
    sudo make install

Tofu
    
    sudo apt-get install autoconf automake libtool libpcre3 libpcre3-dev libfcgi-dev
    git clone git://github.com/AlexBio/Tofu
    cd Tofu
    ./autogen.sh
    ./configure
    make
    sudo make install

0MQ

    sudo apt-get install libzmq-dev libzmq1

libjson

    sudo apt-get install libjson0 libjson0-dev

hiredis

    git clone https://github.com/antirez/hiredis
    cd hiredis
    make
    sudo make install
    sudo ldconfig
    
## Building bungle-o

    make
	
## Using bungle-o

    ./bungelo --server
    ./bungelo --client
    curl -d '{"id" : "bungle-o", "message" : "test message"}' http://localhost:5000
    redis-cli smembers bungelo
