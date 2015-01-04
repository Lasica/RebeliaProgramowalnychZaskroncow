#include "server/Server.h"
#include "server/FakeServer.h"

#include <boost/serialization/base_object.hpp>
#include <iostream>
#include <string>
using namespace boost::asio;
using namespace std;

int main() {

    FakeServer::Strings strIN;
    strIN.push_back("str1");
    strIN.push_back("str2");
    strIN.push_back("str3");
    strIN.push_back("str4");
    strIN.push_back("str5");

    FakeServer fakeS(5, "CHtest", strIN);

    return 0;
}
