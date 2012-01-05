# bungle-o

## Notes

At the moment this only runs on linux. The Tofu library doesn't yet compile against OS X. Once that is resolved everything should work properly on OS X

## Dependencies

For compiling the Tofu library

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

## Building bungle-o

    make
	
## Using bungle-o

    ./server
    ./client
    curl -d '{"id" : "bungle-o", "message" : "test message"}' http://localhost:5000

You should see a message printed from the client every time something is posted to the server
