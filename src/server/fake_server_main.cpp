#include "server/Server.h"
#include "server/FakeServer.h"

#include <boost/serialization/base_object.hpp>
#include <boost/serialization/vector.hpp>
#include <iostream>
#include <string>
using namespace boost::asio;
using namespace std;

int main() {

    FakeServer::Strings strIN;
//    strIN.push_back("0_CHtest");
//    strIN.push_back("1_CHtest");
//    strIN.push_back("2_CHtest");

//    FakeServer fakeS(3, "CHtest", strIN);
//    Packet doomPacket1("bye", CONNECTION_END, 1);
//    Packet doomPacket2("bye", CONNECTION_END, 2);
//    Packet doomPacket3("bye", CONNECTION_END, 3);
//    fakeS.to_send.push(doomPacket1);
//    fakeS.to_send.push(doomPacket2);
//    fakeS.to_send.push(doomPacket3);

//    // Program się kończy, bo wczytywane dane nie są jeszcze zdeserializowane.

//    fakeS.run();

    std::cout << "*** Koniec! ***\n";
    return 0;
}
