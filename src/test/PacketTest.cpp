#define BOOST_TEST_DYN_LINK

#define BOOST_TEST_MODULE PacketTest

#include <boost/test/detail/unit_test_parameters.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

#include <boost/shared_ptr.hpp>


#include "server/Address.hpp"
#include "shared/Resource.hpp"
#include "shared/ChatEntryRaw.hpp"
#include "shared/HandshakeRaw.hpp"
#include "shared/Packet.hpp"
#include <sstream>

#include <fstream>
#include <boost/test/unit_test.hpp>

using namespace boost::unit_test;
// ------------- Tests Follow --------------
BOOST_AUTO_TEST_SUITE( Serializing )

BOOST_AUTO_TEST_CASE( simple_case ) {
//    if( runtime_config::log_level() <= boost::unit_test::log_warnings )
//        unit_test_log.set_threshold_level( boost::unit_test::log_messages );

    ResourcePtr CEptr(new ChatEntryRaw("CEptr", "serializationTest"));
    Packet samplePacket(Packet::Tag::UPDATED_RESOURCE, nullptr, CEptr );

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

    std::string savedResourceContent = samplePacket.show_resource_content();
    Packet::Tag savedPacketTag = samplePacket.get_tag();

    CEptr.reset();  // CEptr does not point to serialized Resource
    BOOST_CHECK_EQUAL(  savedResourceContent,                   restoredPacket.show_resource_content() );
    BOOST_CHECK_EQUAL(  savedPacketTag,                         restoredPacket.get_tag()  );

}


BOOST_AUTO_TEST_CASE( deleting_pointer_to_packet ) {
    // checking what happens if pointer to Packet instance is deleted after its serialization

    ResourcePtr pResource(new ChatEntryRaw("deleting_pointer_to_resource", "TestMSG"));
    Packet* pPacket = new Packet(Packet::Tag::UPDATED_RESOURCE, nullptr, pResource);
    std::ofstream ofs("PACKET_TEST_deleting_pointer_to_packet"); // strumieniem jest tutaj plik

    boost::archive::text_oarchive oaTest(ofs);

    oaTest << pPacket;
    ofs.close();

    // making copies of pPackets fields (for equality test)
    ChatEntryRaw resourceCopy(*reinterpret_cast<ChatEntryRaw*>(&*pResource));
    Packet::Tag savedPacketTag = pPacket->get_tag();


    // deleting this pointer to check, if object can be restored from file
    pResource.reset();
    delete pPacket;

    Packet* pDeserializedPacket;

    std::ifstream ifs("PACKET_TEST_deleting_pointer_to_packet");
    boost::archive::text_iarchive ia(ifs);

    ia >> pDeserializedPacket;
    ifs.close();

    BOOST_CHECK_EQUAL(  pDeserializedPacket->show_resource_content(),   resourceCopy.show_content()  );
    BOOST_CHECK_EQUAL(  savedPacketTag,                                 pDeserializedPacket->get_tag()  );
    BOOST_CHECK_EQUAL(  pDeserializedPacket->get_content()->get_tag(),  Resource::CHAT_ENTRY);
}
BOOST_AUTO_TEST_SUITE_END()




