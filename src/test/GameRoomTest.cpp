#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE GameRoomTest

//#include <boost/test/detail/unit_test_parameters.hpp>
//#include <boost/archive/text_iarchive.hpp>
//#include <boost/archive/text_oarchive.hpp>
//#include <boost/shared_ptr.hpp>


//#include <boost/enable_shared_from_this.hpp>
//#include <boost/asio.hpp>
//#include "shared/typedefinitions.hpp"
//#include "server/Address.hpp"
//#include "shared/Resource.hpp"
//#include "shared/GameRoomRaw.hpp"
#include "shared/GameRoom.hpp"
//#include "server/Client.hpp"
//#include "server/ClientsRegister.hpp"
#include "server/Server.hpp"
#include <fstream>

#include <boost/test/unit_test.hpp>

using namespace boost::unit_test;

BOOST_AUTO_TEST_SUITE( GameRoom_constructor )

BOOST_AUTO_TEST_CASE( essential_test ) {
    Address ad;
    ClientState cs; // default state, (LOBBY, 0)

    ClientID host = TcpServer::getInstance().connectedClients.register_client(&ad, nullptr);

    GameRoom testGR(host, "testGameRoom");


    BOOST_CHECK_EQUAL(  testGR.get_number_of_players(),    1  );
    BOOST_CHECK_EQUAL(  testGR.get_name(), "testGameRoom");
    std::list<std::string> testNames;
    testNames.push_back(TcpServer::getInstance().connectedClients.look_up_with_id(host)->get_nickname());
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(  essential_functionalities )

BOOST_AUTO_TEST_CASE  ( add_player ) {
    Address ad;
    ClientState cs; //default ClientState
    ClientID testHost = TcpServer::getInstance().connectedClients.register_client(&ad, nullptr);
    ClientID testPlayer1 = TcpServer::getInstance().connectedClients.register_client(&ad, nullptr);
    ClientID testPlayer2 = TcpServer::getInstance().connectedClients.register_client(&ad, nullptr);
    BOOST_REQUIRE_EQUAL( TcpServer::getInstance().connectedClients.get_state(testHost).location, cs.location);
    BOOST_REQUIRE_EQUAL( TcpServer::getInstance().connectedClients.get_state(testHost).locationIdentifier, cs.locationIdentifier);
    BOOST_REQUIRE_EQUAL( TcpServer::getInstance().connectedClients.get_state(testPlayer1).location, cs.location);
    BOOST_REQUIRE_EQUAL( TcpServer::getInstance().connectedClients.get_state(testPlayer1).locationIdentifier, cs.locationIdentifier);
    BOOST_REQUIRE_EQUAL( TcpServer::getInstance().connectedClients.get_state(testPlayer2).location, cs.location);
    BOOST_REQUIRE_EQUAL( TcpServer::getInstance().connectedClients.get_state(testPlayer2).locationIdentifier, cs.locationIdentifier);

    GameRoom testGR(testHost, "testGameRoom");
    testGR.add_player(testPlayer1);
    testGR.add_player(testPlayer2);
    ClientState gameroomCs(ClientState::GAMEROOM, testGR.get_id());
    std::cout << "**cs == " << cs.location << ", " << cs.locationIdentifier <<  std::endl;

    std::cout << "**gameroomCs == " << gameroomCs.location << ", " << gameroomCs.locationIdentifier <<  std::endl;
    BOOST_CHECK_EQUAL( TcpServer::getInstance().connectedClients.get_state(testHost).location, gameroomCs.location);
    BOOST_CHECK_EQUAL( TcpServer::getInstance().connectedClients.get_state(testHost).locationIdentifier, gameroomCs.locationIdentifier);
    BOOST_CHECK_EQUAL( TcpServer::getInstance().connectedClients.get_state(testPlayer1).location, gameroomCs.location);
    BOOST_CHECK_EQUAL( TcpServer::getInstance().connectedClients.get_state(testPlayer1).locationIdentifier, gameroomCs.locationIdentifier);
    BOOST_CHECK_EQUAL( TcpServer::getInstance().connectedClients.get_state(testPlayer2).location, gameroomCs.location);
    BOOST_CHECK_EQUAL( TcpServer::getInstance().connectedClients.get_state(testPlayer2).locationIdentifier, gameroomCs.locationIdentifier);
    BOOST_CHECK_EQUAL(  testGR.get_number_of_players(), 3  );
}


BOOST_AUTO_TEST_CASE  ( remove_player ) {
    Address ad;
    ClientState cs; //default ClientState
    ClientID testHost = TcpServer::getInstance().connectedClients.register_client(&ad, nullptr);
    ClientID testPlayer1 = TcpServer::getInstance().connectedClients.register_client(&ad, nullptr);
    ClientID testPlayer2 = TcpServer::getInstance().connectedClients.register_client(&ad, nullptr);

    GameRoom testGR(testHost, "testGameRoom");
    testGR.add_player(testPlayer1);
    testGR.add_player(testPlayer2);
    ClientState gameroomCs(ClientState::GAMEROOM, testGR.get_id());
    // aby ten test miał sens gracze musza być poprawnie dodani do GameRoomu
    BOOST_REQUIRE_EQUAL( TcpServer::getInstance().connectedClients.get_state(testHost).location, gameroomCs.location);
    BOOST_REQUIRE_EQUAL( TcpServer::getInstance().connectedClients.get_state(testHost).locationIdentifier, gameroomCs.locationIdentifier);
    BOOST_REQUIRE_EQUAL( TcpServer::getInstance().connectedClients.get_state(testPlayer1).location, gameroomCs.location);
    BOOST_REQUIRE_EQUAL( TcpServer::getInstance().connectedClients.get_state(testPlayer1).locationIdentifier, gameroomCs.locationIdentifier);
    BOOST_REQUIRE_EQUAL( TcpServer::getInstance().connectedClients.get_state(testPlayer2).location, gameroomCs.location);
    BOOST_REQUIRE_EQUAL( TcpServer::getInstance().connectedClients.get_state(testPlayer2).locationIdentifier, gameroomCs.locationIdentifier);
    BOOST_REQUIRE_EQUAL(  testGR.get_number_of_players(), 3  );

    //usuwanie zwykłego gracza
    testGR.remove_player(testPlayer1);
    BOOST_CHECK_EQUAL( TcpServer::getInstance().connectedClients.get_state(testPlayer1).location, cs.location);
    BOOST_CHECK_EQUAL( TcpServer::getInstance().connectedClients.get_state(testPlayer1).locationIdentifier, cs.locationIdentifier);
    BOOST_CHECK_EQUAL(  testGR.get_number_of_players(), 2  );

    //usuwanie hosta (usuwanie GameRoomu)
    testGR.remove_player(testHost);
    BOOST_CHECK_EQUAL( TcpServer::getInstance().connectedClients.get_state(testPlayer1).location, cs.location);
    BOOST_CHECK_EQUAL( TcpServer::getInstance().connectedClients.get_state(testPlayer1).locationIdentifier, cs.locationIdentifier);
    BOOST_CHECK_EQUAL(  testGR.get_number_of_players(), 0  );
}
BOOST_AUTO_TEST_SUITE_END()


// serializacja
BOOST_AUTO_TEST_SUITE( GameRoom_serialization )

BOOST_AUTO_TEST_CASE( simple_case ) {

    Address ad;
    ClientState cs; //default ClientState
    ClientID testHost = TcpServer::getInstance().connectedClients.register_client(&ad, nullptr);
    ClientID testPlayer1 = TcpServer::getInstance().connectedClients.register_client(&ad, nullptr);
    ClientID testPlayer2 = TcpServer::getInstance().connectedClients.register_client(&ad, nullptr);

    GameRoom sampleGR(testHost, "testGameRoom");
    sampleGR.add_player(testPlayer1);
    sampleGR.add_player(testPlayer2);

    //sprawdzenie, czy GameRoom serializuje się do GameRoomRaw
    std::ofstream ofs("GameRoom_simple_case");
    boost::archive::text_oarchive oa(ofs);
    BOOST_CHECK_NO_THROW(  oa << sampleGR  );
    ofs.close();

    GameRoomRaw restoredGRR;
    std::ifstream ifs("GameRoom_simple_case");
    boost::archive::text_iarchive ia(ifs);
    BOOST_CHECK_NO_THROW(  ia >> restoredGRR  );
    ifs.close();
    std::cout << "***CHECK ID***\n";
    BOOST_CHECK(  typeid(restoredGRR) == typeid(GameRoomRaw) );
    std::cout << "***CHECK ID***\n";

//    BOOST_CHECK_EQUAL(  sampleGR.show_content(),   restoredGRR.show_content()  );
    BOOST_CHECK_EQUAL(  sampleGR.get_id(),   restoredGRR.id );
    BOOST_CHECK_EQUAL(  sampleGR.get_host_id(),   restoredGRR.host  );
    BOOST_CHECK_EQUAL(  sampleGR.get_name(),   restoredGRR.gameRoomName  );
//    BOOST_CHECK_EQUAL_COLLECTIONS(  sampleGR.players.begin(), sampleGR.players.end(),   restoredGRR.players.begin(), restoredGRR.players.end()  );
    BOOST_CHECK_EQUAL(  sampleGR.get_max_number_of_players(),   restoredGRR.maxNumOfPlayers  );
//    BOOST_CHECK_EQUAL(  sampleGR.get_tag(),   restoredGRR.get_tag()  );
}


//BOOST_AUTO_TEST_CASE( wrong_way ) {

//    Address ad;
//    ClientState cs; //default ClientState
//    ClientID testHost = TcpServer::getInstance().connectedClients.register_client(&ad, nullptr);
//    ClientID testPlayer1 = TcpServer::getInstance().connectedClients.register_client(&ad, nullptr);
//    ClientID testPlayer2 = TcpServer::getInstance().connectedClients.register_client(&ad, nullptr);

//    GameRoom sampleGR(testHost, "testGameRoom");
//    sampleGR.add_player(testPlayer1);
//    sampleGR.add_player(testPlayer2);

//    //sprawdzenie, czy GameRoom serializuje się do GameRoomRaw
//    std::ofstream ofs("GameRoom_wrong_way");
//    boost::archive::text_oarchive oa(ofs);
//    BOOST_CHECK_NO_THROW(  oa << sampleGR  );
//    ofs.close();

//    GameRoom restoredGR;
//    std::ifstream ifs("GameRoom_simple_case");
//    boost::archive::text_iarchive ia(ifs);
//    BOOST_CHECK_NO_THROW(  ia >> restoredGR  );
//    ifs.close();

//    BOOST_CHECK(  typeid(restoredGR) == typeid(GameRoom) );
//    //BOOST_CHECK_EQUAL(  sampleGR.show_content(),   restoredGR.show_content()  );
//    BOOST_CHECK_EQUAL(  sampleGR.get_id(),   restoredGR.get_id() );
//    BOOST_CHECK_EQUAL(  sampleGR.get_host_id(),   restoredGR.get_host_id()  );
//    BOOST_CHECK_EQUAL(  sampleGR.get_name(),   restoredGR.get_name()  );
//    //BOOST_CHECK_EQUAL_COLLECTIONS(  sampleGR.players.begin(), sampleGR.players.end(),   restoredGR.players.begin(), restoredGR.players.end()  );
//    BOOST_CHECK_EQUAL(  sampleGR.get_max_number_of_players(),   restoredGR.get_max_number_of_players()  );
//    //BOOST_CHECK_EQUAL(  sampleGR.get_tag(),   restoredGR.get_tag()  );
//}


//BOOST_AUTO_TEST_CASE( deleting_pointer_to_resource ) {

//    std::cout << "***CHECKPOINT***\n";
//    Address ad;
//    ClientState cs; //default ClientState
//    ClientID testHost = TcpServer::getInstance().connectedClients.register_client(&ad, nullptr);
//    ClientID testPlayer1 = TcpServer::getInstance().connectedClients.register_client(&ad, nullptr);
//    ClientID testPlayer2 = TcpServer::getInstance().connectedClients.register_client(&ad, nullptr);

//    GameRoom sampleGR(testHost, "testGameRoom");
//    GameRoomID sampleID = sampleGR.get_id();
//    sampleGR.add_player(testPlayer1);
//    sampleGR.add_player(testPlayer2);
//    std::cout << "***CHECKPOINT***\n";
//    Resource* pResource = &sampleGR;
//    std::cout << "***CHECKPOINT***\n";
//    std::ofstream ofs("GameRoomTest_deleting_pointer_to_resource");
//    std::cout << "***CHECKPOINT***\n";
//    boost::archive::text_oarchive oaTest(ofs);
//    std::cout << "***CHECKPOINT***\n";
//    oaTest.template register_type<GameRoomRaw>();

//    oaTest.template register_type<GameRoom>();

//    std::cout << "***CHECKPOINT***\n";
//    oaTest << pResource;                    //błąd
//    std::cout << "***CHECKPOINT***\n";
//    ofs.close();
//    std::cout << "***CHECKPOINT***\n";
//    delete pResource;   // deleting this pointer to check, if object can be restored from file
//    std::cout << "***CHECKPOINT***\n";
//    Resource *pDeserialized;
//    std::ifstream ifs("ameRoomTest_deleting_pointer_to_resource");
//    boost::archive::text_iarchive ia(ifs);

//    ia >> pDeserialized;
//    ifs.close();

//    GameRoomRaw identicalWithSerialized("testGameRoom", testHost, sampleID);
//    BOOST_CHECK_EQUAL(pDeserialized->show_content(), identicalWithSerialized.show_content());
//}
//BOOST_AUTO_TEST_SUITE_END()
/*
BOOST_AUTO_TEST_CASE( deleting_pointer_to_resource ) {

    Address ad;
    ClientState cs; //default ClientState
    ClientID testHost = TcpServer::getInstance().connectedClients.register_client(&ad, nullptr);
    ClientID testPlayer1 = TcpServer::getInstance().connectedClients.register_client(&ad, nullptr);
    ClientID testPlayer2 = TcpServer::getInstance().connectedClients.register_client(&ad, nullptr);

    //GameRoom* sampleGR = new GameRoom(testHost, "testGameRoom");
    GameRoom* sampleGR = new GameRoom(testHost, "testGameRoom");
    GameRoomID sampleID = sampleGR->get_id();
    sampleGR->add_player(testPlayer1);
    sampleGR->add_player(testPlayer2);
std::cout << "***CHECKPOINT***\n";
    GameRoomRaw* x = new GameRoomRaw(*sampleGR);
    Resource* pResource = x;
    std::ofstream ofs("GameRoomTest_deleting_pointer_to_resource");
    boost::archive::text_oarchive oaTest(ofs);
std::cout << "***CHECKPOINT***\n";

    oaTest << pResource;                    //błąd
    //oaTest << sampleGR;
std::cout << "***CHECKPOINT***\n";
    ofs.close();
    delete pResource;   // deleting this pointer to check, if object can be restored from file
    Resource *pDeserialized;
    std::ifstream ifs("GameRoomTest_deleting_pointer_to_resource");
    boost::archive::text_iarchive ia(ifs);
std::cout << "***CHECKPOINT***\n";
    ia >> pDeserialized;
    ifs.close();

    GameRoomRaw identicalWithSerialized("testGameRoom", testHost, sampleID);
    BOOST_CHECK_EQUAL(pDeserialized->show_content(), identicalWithSerialized.show_content());
}*/

BOOST_AUTO_TEST_SUITE_END()
