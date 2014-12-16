//Link to Boost
#define BOOST_TEST_DYN_LINK

//Define our Module name (prints at testing)
#define BOOST_TEST_MODULE "Przykladowy test"

//VERY IMPORTANT - include this last
#include <boost/test/unit_test.hpp>

//#include ""

// ------------- Tests Follow --------------
BOOST_AUTO_TEST_SUITE( JakisBlokTestow )
BOOST_AUTO_TEST_CASE( JakisAtomowyTest ) {
    BOOST_WARN_MESSAGE(2 == 3, "Ostrzezenie: to tylko szablonowy test");
    BOOST_CHECK_EQUAL(2, 2);
    BOOST_CHECK(true);
    BOOST_CHECK_MESSAGE( 2 == 2, "strony porownania " << 2 << ' ' << 2);
    BOOST_TEST_MESSAGE("Template test message");
    //BOOST_CHECK_THROW() // ma rzucic wyjatek
    //BOOST_CHECK_NO_THROW() // ma nie rzucic wyjatkiem
    //BOOST_ERROR( "BLad, nie przerywa testu");
    BOOST_FAIL("Blad fatalny, przerywa test z negatywnym wynikiem. To template'owy test, wiec ma sie oblewac");
}
BOOST_AUTO_TEST_SUITE_END()
