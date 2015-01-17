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
#include "server/ClientsRegister.hpp"
#include "server/Server.hpp"
#include <fstream>

#include <boost/test/unit_test.hpp>

using namespace boost::unit_test;

//BOOST_AUTO_TEST_SUITE( GameRoom_constructor )

//BOOST_AUTO_TEST_CASE( essential_test ) {
////    /std::cout << "***Checkpont***\n";

//    Address ad;
//    ClientState cs; // default state, (LOBBY, 0)
//    std::cout << "***Checkpoint***\n";
//    Client testHost(ad, nullptr, "host");
//    std::cout << "***Checkpoint***\n";

//    TcpServer.getInstance().register_client(ad, nullptr);
//    std::cout << "***Checkpoint***\n";

//    GameRoom testGR(testHost.get_client_id(), "testGameRoom",  TcpServer.getInstance());
//    std::cout << "***Checkpoint***\n";

//    BOOST_CHECK_EQUAL(  testGR.get_number_of_players(),    1  );
//    BOOST_CHECK_EQUAL(  testGR.gameRoomName, "testGameRoom");
//    std::list<std::string> testNames;
//    testNames.push_back(testHost.get_nickname());
//    BOOST_CHECK_EQUAL_COLLECTIONS( testGR.playersNames.begin(), testGR.playersNames.end(), testNames.begin(), testNames.end() );

//}

//BOOST_AUTO_TEST_SUITE_END()

//BOOST_AUTO_TEST_SUITE(  adding_and_removing_players  )

//BOOST_AUTO_TEST_CASE  ( add_player  ) {
//    Address ad;
//    ClientState cs;
//    ClientPtr testHost(new Client(ad, nullptr, "testHost"));
//    ClientPtr testPlayer1(new Client(ad, nullptr, "testPlayer1"));
//    ClientPtr testPlayer2(new Client(ad, nullptr, "testPlayer2"));

//    GameRoom testGR(testHost, "testGameRoom");
//    testGR.add_player(testPlayer1);
//    testGR.add_player(testPlayer2);
//    BOOST_CHECK_EQUAL(  testGR.get_number_of_players(),    3  );
//}

//BOOST_AUTO_TEST_SUITE_END()


//// serializacja
//BOOST_AUTO_TEST_SUITE( GameRoom_serialization )

//BOOST_AUTO_TEST_CASE( simple_case ) {

//    GameRoom sampleGR = GameRoom();

//    std::ofstream ofs("HandshakeRawTest_simple_case");
//    boost::archive::text_oarchive oa(ofs);
//    BOOST_CHECK_NO_THROW(  oa << sampleHR  );
//    ofs.close();

//    HandshakeRaw restoredHR;
//    std::ifstream ifs("HandshakeRawTest_simple_case");
//    boost::archive::text_iarchive ia(ifs);
//    BOOST_CHECK_NO_THROW(  ia >> restoredHR  );
//    ifs.close();

//    BOOST_CHECK_EQUAL(  sampleHR.show_content(),   restoredHR.show_content()  );
//    BOOST_CHECK_EQUAL(  sampleHR.address_.ip,      restoredHR.address_.ip  );
//    BOOST_CHECK_EQUAL(  sampleHR.address_.port,    restoredHR.address_.port );
//    BOOST_CHECK_EQUAL(  sampleHR.get_tag(),        restoredHR.get_tag()  );
//}


//BOOST_AUTO_TEST_CASE( deleting_pointer_to_resource ) {

//    Address sampleAd(1,2);
//    Resource* pResource = new HandshakeRaw(sampleAd);
//    std::ofstream ofs("HandshakeRawTest_deleting_pointer_to_resource");

//    boost::archive::text_oarchive oaTest(ofs);
//BOOST_AUTO_TEST_CASE( essential_test ) {
//    Address ad;
//    ClientState cs; // default state, (LOBBY, 0)
//    ClientPtr testHost(new Client(&ad, nullptr, "testHost"));

//    oaTest << pResource;
//    ofs.close();

//    delete pResource;   // deleting this pointer to check, if object can be restored from file

//    Resource* pDeserialized;

//    std::ifstream ifs("HandshakeRawTest_deleting_pointer_to_resource");
//    boost::archive::text_iarchive ia(ifs);

//    ia >> pDeserialized;
//    ifs.close();

//    HandshakeRaw identicalWithSerialized(sampleAd);
//BOOST_AUTO_TEST_CASE  ( add_player  ) {
//    Address ad;
//    ClientState cs;
//    ClientPtr testHost(new Client(&ad, nullptr, "testHost"));
//    ClientPtr testPlayer1(new Client(&ad, nullptr, "testPlayer1"));
//    ClientPtr testPlayer2(new Client(&ad, nullptr, "testPlayer2"));

//    BOOST_CHECK_EQUAL(  pDeserialized->show_content(),   identicalWithSerialized.show_content());
//}

//BOOST_AUTO_TEST_SUITE_END()



