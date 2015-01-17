//Link to Boost
#define BOOST_TEST_DYN_LINK

#define BOOST_TEST_MODULE ClientsRegisterTestModule

#include <boost/test/unit_test.hpp>
#include "server/ClientsRegister.hpp"
#include "server/Address.hpp"
#include "server/ClientDataRaw.hpp"
#include "server/Client.hpp"

// TODO: kiedy w ClientsRegister będzie już wybrany kontener i sposób odwoływania się do Clientów

BOOST_AUTO_TEST_SUITE( ClientsRegisterClass )
BOOST_AUTO_TEST_CASE( not_ready ) {

    BOOST_FAIL( "Test not ready yet" );
}
//BOOST_AUTO_TEST_CASE( registering_clients ) {
//    Address sampleAd1(1, 2);
//    ClientState sampleState1(ClientState::GAME, 1);

//    ClientsRegister testRegister;
  //  ClientsRegister::ClientIt client1 = testRegister.register_client("client1", sampleAd1, sampleState1);

//}
//BOOST_AUTO_TEST_CASE( RegisteringClients ) {
//    ClientsRegister::ClientIt it1 = ClientsRegister::instance().register_client("c1", 11, "111.111.111.111", IN_LOBBY, "");
//    ClientsRegister::ClientIt it2 = ClientsRegister::instance().register_client("identicalTest", 44, "100.100.100.100", IN_GAME,
//                                    "identicalGame");
//    ClientsRegister::ClientIt it3 = ClientsRegister::instance().register_client("identicalTest", 44, "100.100.100.100", IN_GAME,
//                                    "identicalGame");

//    BOOST_CHECK(it2 == it3);    //set can't contain 2 identical elements
//}

//BOOST_AUTO_TEST_CASE( Searching ) {
//    ClientsRegister::ClientIt it1 = ClientsRegister::instance().register_client("d1", 11, "111.111.111.111", IN_LOBBY, "");
//    ClientsRegister::ClientIt it2 = ClientsRegister::instance().register_client("d2", 44, "100.100.100.100", IN_GAME, "game1");

//    ClientsRegister::ClientIt test1 = ClientsRegister::instance().look_up_with_nickname("d1");
//    BOOST_CHECK(test1 == it1);

//    ClientsRegister::ClientIt test2 = ClientsRegister::instance().look_up_with_id(it2->get_client_id());
//    BOOST_CHECK(test2 == it2);

//}

//BOOST_AUTO_TEST_CASE( ChangingClientsState ) {
//    ClientsRegister::ClientIt it1 = ClientsRegister::instance().register_client("e1", 11, "111.111.111.111", IN_LOBBY, "");
//    ClientsRegister::ClientIt it2 = ClientsRegister::instance().register_client("e2", 44, "100.100.100.100", IN_GAME, "game1");
//    ClientsRegister::ClientIt it3 = ClientsRegister::instance().register_client("e3", 44, "101.101.101.101", IN_GAME, "game2");

//    ClientsRegister::instance().change_state(it1, IN_GAME);
//    BOOST_CHECK_EQUAL(it1->get_state(), IN_GAME);

//    ClientsRegister::instance().change_state("e2", IN_LOBBY);
//    BOOST_CHECK_EQUAL(it2->get_state(), IN_LOBBY);

//    Client::ClientID id3 = it3->get_client_id();
//    ClientsRegister::instance().change_state(id3, IN_LOBBY);
//    BOOST_CHECK_EQUAL(it3->get_state(), IN_LOBBY);

//}

//BOOST_AUTO_TEST_CASE( RemovingClientsState ) {
//    ClientsRegister::ClientIt it1 = ClientsRegister::instance().register_client("f1", 11, "111.111.111.111", IN_LOBBY, "");
//    ClientsRegister::ClientIt it2 = ClientsRegister::instance().register_client("f2", 44, "100.100.100.100", IN_GAME, "game1");
//    ClientsRegister::ClientIt it3 = ClientsRegister::instance().register_client("f3", 44, "101.101.101.101", IN_GAME, "game2");

//    ClientsRegister::ClientIt END_ITERATOR =
//        ClientsRegister::instance().look_up_with_nickname("This function call will return iterator to the end of set..."); //...
//    ClientsRegister::instance().remove_client(it1);
//    BOOST_CHECK(ClientsRegister::instance().look_up_with_nickname("f1") == END_ITERATOR);

//    ClientsRegister::instance().remove_client("f2");
//    BOOST_CHECK(ClientsRegister::instance().look_up_with_nickname("f2") == END_ITERATOR);

//    Client::ClientID id3 = it3->get_client_id();
//    ClientsRegister::instance().remove_client(id3);
//    BOOST_CHECK(ClientsRegister::instance().look_up_with_nickname("f3") == END_ITERATOR);

//}

BOOST_AUTO_TEST_SUITE_END()























