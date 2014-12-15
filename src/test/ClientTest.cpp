//Link to Boost
#define BOOST_TEST_DYN_LINK

#define BOOST_TEST_MODULE "ClientTestModule"

#include <boost/test/unit_test.hpp>
#include "server/Client.hpp"

BOOST_AUTO_TEST_SUITE( a )
BOOST_AUTO_TEST_CASE( a ) {  
  Client test("test", 12, "testip", IN_GAME, "aa");
}
BOOST_AUTO_TEST_SUITE_END()
