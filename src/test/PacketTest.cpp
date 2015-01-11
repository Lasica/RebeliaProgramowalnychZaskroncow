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

// ------------- Tests Follow --------------
//BOOST_AUTO_TEST_SUITE( Serialsing )
//BOOST_AUTO_TEST_CASE( write_read ) {
//    if( runtime_config::log_level() <= boost::unit_test::log_warnings )
//        unit_test_log.set_threshold_level( boost::unit_test::log_messages );

//    std::stringstream ofs;

//    Packet pOut("Hello! Test data here.", CHAT_ENTRY, 5);

//    {
//        boost::archive::text_oarchive oa(ofs);

//        BOOST_CHECK_NO_THROW( oa << pOut );
//    }

//    Packet pIn;
//    {
//        boost::archive::text_iarchive ia(ofs);
//        BOOST_CHECK_NO_THROW(ia >> pIn);
//        std::cout << " " << pIn.get_data_string() << std::endl;
//    }
//    BOOST_TEST_MESSAGE (ofs);
//    BOOST_CHECK_EQUAL(  pIn.get_data_string()   ,     pOut.get_data_string()    );
//    BOOST_CHECK_EQUAL(  pIn.get_tag()           ,     pOut.get_tag()            );
//    BOOST_CHECK_EQUAL(  pIn.get_data_streambuf(),     pOut.get_data_streambuf() );
//    BOOST_TEST_MESSAGE (std::to_string(pIn.get_address()) + std::string(" ") + std::to_string(pOut.get_address()));

//}

//BOOST_AUTO_TEST_CASE( testing_get_data_streambuf ) {
//    std::stringstream ofs;

//    Packet exemplaryPacket("Hello! Test data here.", CHAT_ENTRY, 5);
//    {
//        boost::archive::text_oarchive oa(ofs);
//        BOOST_CHECK_NO_THROW( oa << exemplaryPacket );
//    }
//    //UWAGA NA VOODOO, w tej linijce dzieje sie MAAAGIAAAA (dlaczego jest potrzebny enter?)
//    Packet::StreamBuffer streambuff = exemplaryPacket.get_data_streambuf() + std::string("\n");
//    BOOST_CHECK_EQUAL( streambuff, ofs.str() );

//    ofs.flush();
//    ofs << exemplaryPacket.get_data_streambuf();

//    Packet readPacket;
//    {
//        boost::archive::text_iarchive ia(ofs);
//        BOOST_CHECK_NO_THROW( ia >> readPacket );
//    }

//    BOOST_CHECK_EQUAL(  exemplaryPacket.get_data_string()   ,     readPacket.get_data_string()    );
//    BOOST_CHECK_EQUAL(  exemplaryPacket.get_tag()           ,     readPacket.get_tag()            );
//    BOOST_CHECK_EQUAL(  exemplaryPacket.get_data_streambuf(),     readPacket.get_data_streambuf() );
//}
//BOOST_AUTO_TEST_SUITE_END()


// nowy test serializacji pakietu

BOOST_AUTO_TEST_SUITE( serializacja )


BOOST_AUTO_TEST_CASE( essential_serialization_tests ) {
/*
    boost::shared_ptr<Resource> pCE(new ChatEntryRaw("TestNick", "TestMSG"));
    Address HSad = { .ip = 5, .port = 11 };
    boost::shared_ptr<Resource> pHS(new HandshakeRaw(HSad));

    // enumy nie chcą się inicjalizować inaczej...
    Packet CEPacket(pCE, static_cast<Packet::Tag(1), 5);
    Packet HSPacket(pHS, static_cast<Packet::Tag>(3), 6);

    std::ofstream ofs("PacketTestFile"); // strumieniem jest tutaj plik

    std::cout << "*** Checkpoint 1***\n";

    boost::archive::text_oarchive oa(ofs);
    std::cout << "*** Checkpoint 2***\n";

    oa << CEPacket;
    oa << HSPacket;
    ofs.close();


    Packet CEPacketDeserialized, HSPacketDeserialized;  //nowe obiekty, które przyjmą zdeserializowane dane

    std::ifstream ifs("PacketTestFile");
    boost::archive::text_iarchive ia(ifs);
    std::cout << "*** Checkpoint 3***\n";

    ia >> CEPacketDeserialized;
    ia >> HSPacketDeserialized;
    ifs.close();
    BOOST_CHECK_EQUAL(CEPacketDeserialized.show_resource_content(), CEPacket.show_resource_content());
    BOOST_CHECK_EQUAL(HSPacketDeserialized.show_resource_content(), HSPacket.show_resource_content());
*/
}

BOOST_AUTO_TEST_SUITE_END()





