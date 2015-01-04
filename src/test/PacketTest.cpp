#define BOOST_TEST_DYN_LINK

#define BOOST_TEST_MODULE PacketTest

#include <boost/test/unit_test.hpp>
#include <boost/test/detail/unit_test_parameters.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

#include "shared/Packet.hpp"
#include <sstream>

using namespace boost::unit_test;

// ------------- Tests Follow --------------
BOOST_AUTO_TEST_SUITE( Serialsing )
BOOST_AUTO_TEST_CASE( write_read ) {
    if( runtime_config::log_level() <= boost::unit_test::log_warnings )
        unit_test_log.set_threshold_level( boost::unit_test::log_messages );

    std::stringstream ofs;

    Packet pOut("Hello! Test data here.", CHAT_ENTRY, 5);

    {
        boost::archive::text_oarchive oa(ofs);

        BOOST_CHECK_NO_THROW( oa << pOut );
    }

    Packet pIn;
    {
        boost::archive::text_iarchive ia(ofs);
        BOOST_CHECK_NO_THROW(ia >> pIn);
        std::cout << " " << pIn.get_data_string() << std::endl;
    }
    BOOST_TEST_MESSAGE (ofs);
    BOOST_CHECK(pIn.get_data_string() == pOut.get_data_string());
    BOOST_CHECK(pIn.get_tag() == pOut.get_tag());
    BOOST_CHECK(pIn.get_data_streambuf() == pOut.get_data_streambuf());
    BOOST_TEST_MESSAGE (std::to_string(pIn.get_address()) + std::string(" ") + std::to_string(pOut.get_address()));

}
BOOST_AUTO_TEST_SUITE_END()








