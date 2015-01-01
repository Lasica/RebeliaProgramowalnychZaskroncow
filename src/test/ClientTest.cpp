//Link to Boost
#define BOOST_TEST_DYN_LINK

#define BOOST_TEST_MODULE ClientTestModule

#include <boost/test/unit_test.hpp>
<<<<<<< HEAD
#include "server/Client.hpp" // includować Clienta

//BOOST_AUTO_TEST_SUITE(  )  to nie jest wymagane, kategoria testu, można pominąć
//BOOST_AUTO_TEST_CASE( ) {  }  tyle ile rzeczy do przetestowania
//BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_CASE( ISINGAMETEST ) {

   Client test=Client("test", 12,"testip", IN_GAME, "aa");
   BOOST_CHECK(test.is_in_game());
    int a=4;
    BOOST_CHECK(a==4);
}
/*
BOOST_AUTO_TEST_CASE(c-tor)
// porównywanie p
*/
=======
#include "server/Client.hpp"

BOOST_AUTO_TEST_SUITE( a )
BOOST_AUTO_TEST_CASE( a ) {  
  Client test("test", 12, "testip", IN_GAME, "aa");
}
BOOST_AUTO_TEST_SUITE_END()
>>>>>>> 37686bd79dce0a83514fe65e5570006cfdb231e0
