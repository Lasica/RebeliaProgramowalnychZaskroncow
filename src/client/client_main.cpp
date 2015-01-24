#include "client.hpp"
#include <boost/thread/thread.hpp>

int main(int argc, char *argv[]) {

    if(argc != 3) {
        std::cout << "usage: ip port \n";
        return 1;


    }

    std::string addrStr(argv[1]);
    short port = atoi(argv[2]);

    io_service io;
    client cli(addrStr, port, io);
    boost::thread th ( boost::bind(io_service::run, &io));
    HandshakeRaw packet;
    cli.start();
    cli.read();
    cli.send(packet);
    return 0;
}
