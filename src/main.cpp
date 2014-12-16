#include "server.h"
using boost::asio::ip::tcp;
using namespace boost::asio;
int main() {
    try {
        boost::asio::io_service io_service;
        tcpServer server(io_service);
        io_service.run();
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
