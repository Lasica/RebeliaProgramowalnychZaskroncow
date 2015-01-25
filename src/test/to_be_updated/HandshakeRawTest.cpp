#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE HandshakeRawTest

#include <boost/test/detail/unit_test_parameters.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/shared_ptr.hpp>


#include "server/Address.hpp"
#include "shared/Resource.hpp"
#include "shared/HandshakeRaw.hpp"
#include <fstream>

#include <boost/test/unit_test.hpp>

BOOST_CLASS_EXPORT(HandshakeRaw)
using namespace boost::unit_test;
BOOST_AUTO_TEST_SUITE( HandshakeRaw_serialization )

BOOST_AUTO_TEST_CASE( simple_case ) {

    HandshakeRaw sampleHR = HandshakeRaw("Jakuza");

    std::ofstream ofs("HandshakeRawTest_simple_case");
    boost::archive::text_oarchive oa(ofs);
    BOOST_CHECK_NO_THROW(  oa << sampleHR  );
    ofs.close();

    HandshakeRaw restoredHR("");
    std::ifstream ifs("HandshakeRawTest_simple_case");
    boost::archive::text_iarchive ia(ifs);
    BOOST_CHECK_NO_THROW(  ia >> restoredHR  );
    ifs.close();

    BOOST_CHECK_EQUAL(  sampleHR.show_content(),   restoredHR.show_content()  );
    BOOST_CHECK_EQUAL(  sampleHR.get_tag(),        restoredHR.get_tag()  );
}


BOOST_AUTO_TEST_CASE( deleting_pointer_to_resource ) {
    Resource* pResource = new HandshakeRaw("Charlie");
    std::ofstream ofs("HandshakeRawTest_deleting_pointer_to_resource");

    boost::archive::text_oarchive oaTest(ofs);

    oaTest << pResource;
    ofs.close();

    delete pResource;   // deleting this pointer to check, if object can be restored from file

    Resource* pDeserialized;

    std::ifstream ifs("HandshakeRawTest_deleting_pointer_to_resource");
    boost::archive::text_iarchive ia(ifs);

    ia >> pDeserialized;
    ifs.close();

    HandshakeRaw identicalWithSerialized("Charlie");

    BOOST_CHECK_EQUAL(  pDeserialized->show_content(),   identicalWithSerialized.show_content());
}

BOOST_AUTO_TEST_SUITE_END()
