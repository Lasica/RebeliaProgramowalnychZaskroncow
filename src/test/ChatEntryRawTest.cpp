//Link to Boost
#define BOOST_TEST_DYN_LINK

//Define our Module name (prints at testing)
#define BOOST_TEST_MODULE "Przykladowy test"

//VERY IMPORTANT - include this last
#include <boost/test/unit_test.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

#include "shared/ChatEntryRaw.h"
#include <iostream>
#include <fstream>

// ------------- Tests Follow --------------
BOOST_AUTO_TEST_SUITE( serialsing )
BOOST_AUTO_TEST_CASE( write_read ) {

    // create and open a character archive for output
    std::stringstream ofs;

    // create class instance
    const ChatEntryRaw g("John", " siema! ");

    // save data to archive
    {
        boost::archive::text_oarchive oa(ofs);
        // write class instance to archive
        BOOST_CHECK_NO_THROW( oa << g );
        // archive and stream closed when destructors are called
    }
    BOOST_TEST_MESSAGE (ofs);

    // ... some time later restore the class instance to its orginal state
    ChatEntryRaw newg;
    {
        // create and open an archive for input
        //std::ifstream ifs("filename");
        boost::archive::text_iarchive ia(ofs);
        // read class state from archive
        BOOST_CHECK_NO_THROW(ia >> newg);
        // archive and stream closed when destructors are called
        std::cout << " " << newg.nick_ << newg.message_;
    }
    BOOST_CHECK(newg.nick_ == g.nick_);
    BOOST_CHECK(newg.message_ == g.message_);

}
BOOST_AUTO_TEST_SUITE_END()
