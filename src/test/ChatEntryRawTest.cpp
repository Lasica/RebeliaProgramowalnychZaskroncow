#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE ChatEntryRawTest

#include <boost/test/detail/unit_test_parameters.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/shared_ptr.hpp>


#include "server/Address.hpp"
#include "shared/Resource.hpp"
#include "shared/ChatEntryRaw.hpp"

#include <fstream>

#include <boost/test/unit_test.hpp>

using namespace boost::unit_test;

BOOST_AUTO_TEST_SUITE( ChatEntryRaw_serialization )

BOOST_AUTO_TEST_CASE( simple_case ) {
//    if( runtime_config::log_level() <= boost::unit_test::log_warnings )
//        unit_test_log.set_threshold_level( boost::unit_test::log_messages );

    ChatEntryRaw sampleCER = ChatEntryRaw("CERptr", "serializationTest");

    std::ofstream ofs("ChatEntryRawTest_simple_case");
    boost::archive::text_oarchive oa(ofs);
    BOOST_CHECK_NO_THROW(  oa << sampleCER  );
    ofs.close();

    ChatEntryRaw restoredCER;
    std::ifstream ifs("ChatEntryRawTest_simple_case");
    boost::archive::text_iarchive ia(ifs);
    BOOST_CHECK_NO_THROW(  ia >> restoredCER  );
    ifs.close();

    BOOST_CHECK_EQUAL(  sampleCER.show_content(),   restoredCER.show_content()  );
    BOOST_CHECK_EQUAL(  sampleCER.nick_,            restoredCER.nick_  );
    BOOST_CHECK_EQUAL(  sampleCER.message_,         restoredCER.message_ );
    BOOST_CHECK_EQUAL(  sampleCER.get_tag(),        restoredCER.get_tag()  );
}

BOOST_AUTO_TEST_CASE( deleting_pointer_to_resource ) {

    Resource *pResource = new ChatEntryRaw("deleting_pointer_to_resource", "TestMSG");
    std::cout << "***Checkpoint***\n";

    std::ofstream ofs("ChatEntryRawTest_deleting_pointer_to_resource"); // strumieniem jest tutaj plik
    std::cout << "***Checkpoint***\n";

    boost::archive::text_oarchive oaTest(ofs);
    std::cout << "***Checkpoint***\n";

    oaTest << pResource;
    std::cout << "***Checkpoint***\n";

    ofs.close();
    std::cout << "***Checkpoint***\n";

    delete pResource;   // deleting this pointer to check, if object can be restored from file

    Resource *pDeserialized;

    std::ifstream ifs("ChatEntryRawTest_deleting_pointer_to_resource");
    boost::archive::text_iarchive ia(ifs);

    ia >> pDeserialized;
    ifs.close();

    ChatEntryRaw identicalWithSerialized("deleting_pointer_to_resource", "TestMSG");

    BOOST_CHECK_EQUAL(pDeserialized->show_content(), identicalWithSerialized.show_content());

}
BOOST_AUTO_TEST_SUITE_END()
