#define BOOST_TEST_DYN_LINK

#define BOOST_TEST_MODULE ClientTestModule

#include <boost/test/unit_test.hpp>
#include "server/Client.hpp"

BOOST_AUTO_TEST_SUITE( ConstructorsTests )

BOOST_AUTO_TEST_CASE( ParametrizedCtor1 ) {

    Client test = Client("test", 12, boost::asio::ip::address::from_string("125.0.0.145"), IN_GAME, "ParametrizedCtor1");

    BOOST_CHECK_EQUAL(test.get_nickname(), "test");
    BOOST_CHECK_EQUAL(test.get_port(), 12);
    BOOST_CHECK_EQUAL(test.get_ip(), boost::asio::ip::address::from_string("125.0.0.145"));
    BOOST_CHECK_EQUAL(test.get_ip_str(), "125.0.0.145");
    BOOST_CHECK_EQUAL(test.get_state(), IN_GAME);
    BOOST_CHECK_EQUAL(test.get_game_id(), "ParametrizedCtor1");
    BOOST_CHECK_EQUAL(test.get_client_id(), 0);
}

BOOST_AUTO_TEST_CASE( ParametrizedCtor2 ) {

    Client test = Client("test", 12, "125.0.0.145", IN_GAME, "ParametrizedCtor2");

    BOOST_CHECK_EQUAL(test.get_nickname(), "test");
    BOOST_CHECK_EQUAL(test.get_port(), 12);
    BOOST_CHECK_EQUAL(test.get_ip(), boost::asio::ip::address::from_string("125.0.0.145"));
    BOOST_CHECK_EQUAL(test.get_ip_str(), "125.0.0.145");
    BOOST_CHECK_EQUAL(test.get_state(), IN_GAME);
    BOOST_CHECK_EQUAL(test.get_game_id(), "ParametrizedCtor2");
    BOOST_CHECK_EQUAL(test.get_client_id(), 1);

}

BOOST_AUTO_TEST_CASE( CopyCtor ) {

    Client sample = Client("sample", 12, "125.0.0.145", IN_GAME, "CopyCtor");
    Client copy(sample);
    BOOST_CHECK_EQUAL(copy.get_nickname(), "sample");
    BOOST_CHECK_EQUAL(copy.get_port(), 12);
    BOOST_CHECK_EQUAL(copy.get_ip(), boost::asio::ip::address::from_string("125.0.0.145"));
    BOOST_CHECK_EQUAL(copy.get_ip_str(), "125.0.0.145");
    BOOST_CHECK_EQUAL(copy.get_state(), IN_GAME);
    BOOST_CHECK_EQUAL(copy.get_game_id(), "CopyCtor");
    BOOST_CHECK_EQUAL(copy.get_client_id(), 2);
    BOOST_CHECK_EQUAL(copy.get_client_id(), copy.get_client_id());
}

BOOST_AUTO_TEST_CASE( IDGeneration ) {

    Client id3("id3", 12, "125.0.0.145", IN_GAME, "idTest");
    Client id4("id4", 12, "125.0.0.145", IN_GAME, "idTest");
    Client id4copy(id4);

    BOOST_CHECK_EQUAL(id3.get_client_id(), 3);
    BOOST_CHECK_EQUAL(id4.get_client_id(), 4);
    BOOST_CHECK_EQUAL(id4.get_client_id(), id4.get_client_id());

}

BOOST_AUTO_TEST_SUITE_END()




BOOST_AUTO_TEST_SUITE( SetMethods )

Client setTests("setTest", 12, "125.0.0.145", IN_GAME, "gameID1");

BOOST_AUTO_TEST_CASE( State ) {

    setTests.set_state(IN_LOBBY);
    BOOST_CHECK_EQUAL(setTests.get_state(), IN_LOBBY);
}

BOOST_AUTO_TEST_CASE( GameID ) {

    setTests.set_game_id("testID");
    BOOST_CHECK_EQUAL(setTests.get_game_id(), "testID");

}

BOOST_AUTO_TEST_SUITE_END()




BOOST_AUTO_TEST_SUITE( OperatorLessThan )

Client opTest1("operatorTestA", 12, "125.0.0.145", IN_GAME, "opTest");
Client opTest2("operatorTestA", 12, "255.255.255.255", IN_GAME, "opTest");
Client opTest3("operatorTestB", 12, "125.0.0.145", IN_GAME, "opTest");
Client opTest4("operatorTestC", 12, "255.255.255.255", IN_GAME, "opTest");

BOOST_AUTO_TEST_CASE( DifferentIPsAndNicks ) {
    BOOST_CHECK( opTest1 < opTest4 );
    BOOST_CHECK( !(opTest4 < opTest1) );
}

BOOST_AUTO_TEST_CASE( DifferentIPs ) {
    BOOST_CHECK( opTest1 < opTest2 );
    BOOST_CHECK( !(opTest2 < opTest1) );
}

BOOST_AUTO_TEST_CASE( DifferentNicks ) {
    BOOST_CHECK( opTest1 < opTest3 );
    BOOST_CHECK( !(opTest3 < opTest1) );
}

BOOST_AUTO_TEST_CASE( Equal ) {
    BOOST_CHECK( !(opTest1 < opTest1) );

}

BOOST_AUTO_TEST_SUITE_END()












