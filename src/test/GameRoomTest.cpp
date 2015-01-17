#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE GameRoomTest

#include <boost/test/detail/unit_test_parameters.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/shared_ptr.hpp>

#include "shared/typedefinitions.hpp"
#include "server/Address.hpp"
#include "shared/Resource.hpp"
#include "shared/GameRoomRaw.hpp"
#include "shared/GameRoom.hpp"
#include "server/Client.hpp"

#include <fstream>

#include <boost/test/unit_test.hpp>

using namespace boost::unit_test;

BOOST_AUTO_TEST_SUITE( GameRoom_constructor )

BOOST_AUTO_TEST_CASE( essential_test ) {
    Address ad;
    ClientState cs; // default state, (LOBBY, 0)
    ClientPtr testHost(new Client(ad, nullptr, "testHost"));

    GameRoom testGR(testHost, "testGameRoom");

    BOOST_CHECK_EQUAL(  testGR.get_number_of_players(),    1  );
    BOOST_CHECK_EQUAL(  testGR.gameRoomName,                "testGameRoom");
    std::list<std::string> testNames;
    testNames.push_back(testHost->get_nickname());
    BOOST_CHECK_EQUAL_COLLECTIONS( testGR.playersNames.begin(), testGR.playersNames.end(), testNames.begin(), testNames.end() );

}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(  adding_and_removing_players  )

BOOST_AUTO_TEST_CASE  ( add_player  ) {
    Address ad;
    ClientState cs;
    ClientPtr testHost(new Client(ad, nullptr, "testHost"));
    ClientPtr testPlayer1(new Client(ad, nullptr, "testPlayer1"));
    ClientPtr testPlayer2(new Client(ad, nullptr, "testPlayer2"));

    GameRoom testGR(testHost, "testGameRoom");
    testGR.add_player(testPlayer1);
    testGR.add_player(testPlayer2);
    BOOST_CHECK_EQUAL(  testGR.get_number_of_players(),    3  );
}

BOOST_AUTO_TEST_SUITE_END()



