//Link to Boost
#define BOOST_TEST_DYN_LINK

#define BOOST_TEST_MODULE ClientsRegisterTestModule

#include <boost/test/unit_test.hpp>
#include "server/ClientsRegister.hpp"
#include "server/Address.hpp"
#include <boost/thread.hpp>

BOOST_AUTO_TEST_SUITE( ClientsRegister_essential_tests )

BOOST_AUTO_TEST_CASE( registering_and_removing_clients ) {
    // testowane na TcpPointerach==nullptr, bo nie wiem, czy potrzebne są testy z niezerowymi wskaźnikami

    Address ad;
    ClientsRegister testCR;

    ClientID id1 = testCR.register_client(&ad, nullptr);
    ClientID id2 = testCR.register_client(&ad, nullptr);
    ClientID id3 = testCR.register_client(&ad, nullptr);

    ClientPtr pt1 = testCR.look_up_with_id(id1); // teraz każdy ze wskaźników powinien 2 właścicieli
    ClientPtr pt2 = testCR.look_up_with_id(id2);
    ClientPtr pt3 = testCR.look_up_with_id(id3);

    BOOST_CHECK_EQUAL( pt1.use_count(), 2 );
    BOOST_CHECK_EQUAL( pt2.use_count(), 2 );
    BOOST_CHECK_EQUAL( pt3.use_count(), 2 );


    BOOST_CHECK_EQUAL( testCR.get_size(), 3 );
    BOOST_CHECK( pt1->get_client_id() != pt2->get_client_id());

    testCR.remove_client(id2);
    BOOST_CHECK_EQUAL( testCR.get_size(), 2 );
    BOOST_CHECK_EQUAL( pt2.use_count(), 1 );    // sprawdzenie, czy zaalokowana pamięć jest zwalniana

    testCR.remove_client(pt1->get_client_id());
    BOOST_CHECK_EQUAL( testCR.get_size(), 1 );
    BOOST_CHECK_EQUAL( pt1.use_count(), 1 );

    testCR.remove_client(id3);
    BOOST_CHECK_EQUAL( testCR.get_size(), 0 );
    BOOST_CHECK_EQUAL( pt3.use_count(), 1 );

}


BOOST_AUTO_TEST_CASE( look_up_method ) {
    Address ad;
    ClientsRegister testCR;

    ClientID id1 = testCR.register_client(&ad, nullptr);
    ClientID id2 = testCR.register_client(&ad, nullptr);

    BOOST_CHECK( testCR.look_up_with_id(id1) != nullptr );
    testCR.remove_client(id2);
    BOOST_CHECK_NO_THROW( testCR.look_up_with_id(id2) );
}


BOOST_AUTO_TEST_CASE( change_state_method ) {
    Address ad;
    ClientsRegister testCR;

    ClientID id1 = testCR.register_client(&ad, nullptr);
    ClientID id2 = testCR.register_client(&ad, nullptr);

    ClientState def;

    BOOST_CHECK_EQUAL( testCR.get_state(id1).location, def.location );
    BOOST_CHECK_EQUAL( testCR.get_state(id1).locationIdentifier, def.locationIdentifier );
    ClientState state(ClientState::GAMEROOM, 5);
    testCR.change_state(id2, state);

    BOOST_CHECK_EQUAL( testCR.get_state(id2).location, ClientState::GAMEROOM );
    BOOST_CHECK_EQUAL( testCR.get_state(id2).locationIdentifier, 5 );
}

BOOST_AUTO_TEST_SUITE_END()
