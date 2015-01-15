#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE ClientDataRawTest

#include <boost/test/detail/unit_test_parameters.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/shared_ptr.hpp>

#include "shared/typedefinitions.h"
#include "server/ClientDataRaw.h"
#include "shared/Resource.h"
#include <fstream>

#include <boost/test/unit_test.hpp>

using namespace boost::unit_test;

BOOST_AUTO_TEST_SUITE( ClientDataRaw_serialization )

BOOST_AUTO_TEST_CASE( simple_case ) {

    ClientState testState(ClientState::LOBBY, 0);
    ClientDataRaw sampleCDR(testState, 1);

    std::ofstream ofs("ClientDataRawTest_simple_case");
    boost::archive::text_oarchive oa(ofs);
    BOOST_CHECK_NO_THROW(  oa << sampleCDR  );
    ofs.close();

    ClientDataRaw restoredCDR;
    std::ifstream ifs("ClientDataRawTest_simple_case");
    boost::archive::text_iarchive ia(ifs);
    BOOST_CHECK_NO_THROW(  ia >> restoredCDR  );
    ifs.close();

    //odkomentować, jeśli ClientDataRaw odziedziczy po Resource
    //BOOST_CHECK_EQUAL(  sampleCDR.show_content(),   restoredCDR.show_content()  );
    BOOST_CHECK_EQUAL(  sampleCDR.clientID_,                    restoredCDR.clientID_  );
    BOOST_CHECK_EQUAL(  sampleCDR.state_.location,              restoredCDR.state_.location );
    BOOST_CHECK_EQUAL(  sampleCDR.state_.locationIdentifier,    restoredCDR.state_.locationIdentifier  );
}

BOOST_AUTO_TEST_SUITE_END()
