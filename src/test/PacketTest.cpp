#define BOOST_TEST_DYN_LINK

#define BOOST_TEST_MODULE PacketTest

#include <boost/test/unit_test.hpp>
#include <boost/test/detail/unit_test_parameters.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

#include <boost/shared_ptr.hpp>


#include "server/Address.hpp"
#include "shared/Resource.h"
#include "shared/ChatEntryRaw.h"
#include "shared/HandshakeRaw.hpp"
#include "shared/Packet.hpp"
#include <sstream>

#include <fstream>

using namespace boost::unit_test;
/*FIXME: Adres IP na string
// ------------- Tests Follow --------------
BOOST_AUTO_TEST_SUITE( Serializing )

BOOST_AUTO_TEST_CASE( simple_case ) {
//    if( runtime_config::log_level() <= boost::unit_test::log_warnings )
//        unit_test_log.set_threshold_level( boost::unit_test::log_messages );

    boost::shared_ptr<Resource> CEptr(new ChatEntryRaw("CEptr", "serializationTest"));
    Packet samplePacket(CEptr, Packet::RESOURCE, Address());

    std::ofstream ofs("PacketTest_simple_case");
    boost::archive::text_oarchive oa(ofs);
    BOOST_CHECK_NO_THROW(  oa << samplePacket  );
    ofs.close();

    Packet restoredPacket;
    std::ifstream ifs("PacketTest_simple_case");
    boost::archive::text_iarchive ia(ifs);
    BOOST_CHECK_NO_THROW(  ia >> restoredPacket  );
    ifs.close();

    BOOST_CHECK_EQUAL(  samplePacket.show_resource_content(),   restoredPacket.show_resource_content()  );
    BOOST_CHECK_EQUAL(  samplePacket.get_tag(),                 restoredPacket.get_tag()  );
    BOOST_CHECK_EQUAL(  samplePacket.get_address().ip,          restoredPacket.get_address().ip  );
    BOOST_CHECK_EQUAL(  samplePacket.get_address().port,        restoredPacket.get_address().port  );

    std::string savedResourceContent = samplePacket.show_resource_content();
    Packet::Tag savedPacketTag = samplePacket.get_tag();
    const Address& savedPacketAdress = samplePacket.get_address();

    CEptr.reset();  // CEptr does not point to serialized Resource
    BOOST_CHECK_EQUAL(  savedResourceContent,                   restoredPacket.show_resource_content() );
    BOOST_CHECK_EQUAL(  savedPacketTag,                         restoredPacket.get_tag()  );
    BOOST_CHECK_EQUAL(  savedPacketAdress.ip,                   restoredPacket.get_address().ip  );
    BOOST_CHECK_EQUAL(  savedPacketAdress.port,                 restoredPacket.get_address().port  );

}


BOOST_AUTO_TEST_CASE( deleting_pointer_to_packet ) {
    // checking what happens if pointer to Packet instance is deleted after its serialization

    Resource* pResource = new ChatEntryRaw("deleting_pointer_to_resource", "TestMSG");
    Packet* pPacket = new Packet(pResource, Packet::RESOURCE, Address(1, 2));
    std::ofstream ofs("PACKET_TEST_deleting_pointer_to_packet"); // strumieniem jest tutaj plik

    boost::archive::text_oarchive oaTest(ofs);

    oaTest << pPacket;
    ofs.close();

    // making copies of pPackets fields (for equality test)
    ChatEntryRaw resourceCopy("deleting_pointer_to_resource", "TestMSG");
    Packet::Tag savedPacketTag = pPacket->get_tag();
    const Address savedPacketAdress = pPacket->get_address();


    // deleting this pointer to check, if object can be restored from file
    delete pPacket;

    Packet* pDeserializedPacket;

    std::ifstream ifs("PACKET_TEST_deleting_pointer_to_packet");
    boost::archive::text_iarchive ia(ifs);

    ia >> pDeserializedPacket;
    ifs.close();

    BOOST_CHECK_EQUAL(  pDeserializedPacket->show_resource_content(),   resourceCopy.show_content()  );
    BOOST_CHECK_EQUAL(  savedPacketTag,                                 pDeserializedPacket->get_tag()  );
    BOOST_CHECK_EQUAL(  savedPacketAdress.ip,                           pDeserializedPacket->get_address().ip  );
    BOOST_CHECK_EQUAL(  savedPacketAdress.port,                         pDeserializedPacket->get_address().port  );}

BOOST_AUTO_TEST_SUITE_END()

*/



