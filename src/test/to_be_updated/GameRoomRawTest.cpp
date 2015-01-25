#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE GameRoomRawTest

#include <boost/test/detail/unit_test_parameters.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/shared_ptr.hpp>

#include "server/Address.hpp"
#include "server/Client.hpp"
#include "shared/Resource.hpp"
#include "shared/GameRoomRaw.hpp"
#include <fstream>

#include <boost/test/unit_test.hpp>

using namespace boost::unit_test;

BOOST_AUTO_TEST_SUITE( GameRoomRaw_serialization )

BOOST_AUTO_TEST_CASE( simple_case ) {

    GameRoomRaw sampleGRR = GameRoomRaw("GameRoomRawTest", 5, 1);

    std::ofstream ofs("GameRoomRawTest_simple_case");
    boost::archive::text_oarchive oa(ofs);
    BOOST_CHECK_NO_THROW(  oa << sampleGRR  );
    ofs.close();

    GameRoomRaw restoredGRR;
    std::ifstream ifs("GameRoomRawTest_simple_case");
    boost::archive::text_iarchive ia(ifs);
    BOOST_CHECK_NO_THROW(  ia >> restoredGRR  );
    ifs.close();

    BOOST_CHECK_EQUAL(  sampleGRR.show_content(),   restoredGRR.show_content()  );
    BOOST_CHECK_EQUAL(  sampleGRR.gameRoomName,     restoredGRR.gameRoomName  );
    BOOST_CHECK_EQUAL(  sampleGRR.id ,  restoredGRR.id );
    BOOST_CHECK_EQUAL(  sampleGRR.host,  restoredGRR.host );
    BOOST_CHECK_EQUAL(  sampleGRR.get_tag(),    restoredGRR.get_tag()  );
    BOOST_CHECK_EQUAL_COLLECTIONS(  sampleGRR.players.begin(),  sampleGRR.players.end(), restoredGRR.players.begin(),
                                    restoredGRR.players.end() );
}


BOOST_AUTO_TEST_CASE( deleting_pointer_to_resource ) {

    Resource *pResource = new GameRoomRaw("deleting_pointer_to_resource", 12, 6);
    std::ofstream ofs("GameRoomRawTest_deleting_pointer_to_resource");
    boost::archive::text_oarchive oaTest(ofs);

    oaTest << pResource;
    ofs.close();

    delete pResource;   // deleting this pointer to check, if object can be restored from file

    Resource *pDeserialized;

    std::ifstream ifs("GameRoomRawTest_deleting_pointer_to_resource");
    boost::archive::text_iarchive ia(ifs);

    ia >> pDeserialized;
    ifs.close();

    GameRoomRaw identicalWithSerialized("deleting_pointer_to_resource", 12, 6);

    BOOST_CHECK_EQUAL(  pDeserialized->show_content(), identicalWithSerialized.show_content());
}

BOOST_AUTO_TEST_SUITE_END()
