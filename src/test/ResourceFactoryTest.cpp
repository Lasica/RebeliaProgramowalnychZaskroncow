//Link to Boosti
#define BOOST_TEST_DYN_LINK

//Define our Module name (prints at testing)
#define BOOST_TEST_MODULE "FactoryTestModule"

//VERY IMPORTANT - include this last
#include <boost/test/unit_test.hpp>

#include "shared/ResourceFactory.h"

// ------------- Tests Follow --------------
BOOST_AUTO_TEST_CASE( assignment )
{

    BOOST_CHECK_EQUAL(2,3);
}
