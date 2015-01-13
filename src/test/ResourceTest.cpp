#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE ResourceTest

#include <boost/test/unit_test.hpp>
#include <boost/test/detail/unit_test_parameters.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/shared_ptr.hpp>


#include "server/Address.hpp"
#include "shared/Resource.h"
#include "shared/ChatEntryRaw.h"
#include "shared/HandshakeRaw.hpp"
#include <fstream>

// czy testować tę klasę? - nie ma żadnych niewirtualnych metod


using namespace boost::unit_test;
// ------------- Tests Follow --------------
//BOOST_AUTO_TEST_SUITE( serialization )

//BOOST_AUTO_TEST_CASE( deleting_pointer_to_resource ) {

//    Resource* pResource = new ChatEntryRaw("deleting_pointer_to_resource", "TestMSG");
//    std::ofstream ofs("PACKET_TEST_deleting_pointer_to_resource"); // strumieniem jest tutaj plik

//    boost::archive::text_oarchive oaTest(ofs);

//    oaTest << pResource;
//    ofs.close();

//    delete pResource;   // deleting this pointer to check, if object can be restored from file

//    Resource* pDeserialized;

//    std::ifstream ifs("PACKET_TEST_deleting_pointer_to_resource");
//    boost::archive::text_iarchive ia(ifs);

//    ia >> pDeserialized;
//    ifs.close();

//    ChatEntryRaw identicalWithSerialized("deleting_pointer_to_resource", "TestMSG");

//    BOOST_CHECK_EQUAL(pDeserialized->show_content(), identicalWithSerialized.show_content());

//}
//BOOST_AUTO_TEST_SUITE_END()
