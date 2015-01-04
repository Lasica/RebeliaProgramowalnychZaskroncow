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
    strIN.push_back("0_CHtest");
    strIN.push_back("1_CHtest");
    strIN.push_back("2_CHtest");

    FakeServer fakeS(3, "CHtest", strIN);
    fakeS.run();

    return 0;
}
