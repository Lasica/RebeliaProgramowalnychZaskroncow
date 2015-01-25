#include <sstream>
#include "shared/Packet.hpp"
#include <boost/shared_ptr.hpp>
#include <boost/archive/text_oarchive.hpp>
#include "shared/HandshakeRaw.hpp"
#include "shared/ChatEntryRaw.hpp"
#include "shared/GameRoomRaw.hpp"
#include "server/ClientDataRaw.hpp"
BOOST_CLASS_EXPORT(ChatEntryRaw)
BOOST_CLASS_EXPORT(HandshakeRaw)

Packet::Packet(Tag tag__, const Address *ad__, Resource *content__) :
    content_(content__),
    tag_(tag__),
    address_(ad__) {
    ;
}

Packet::Packet(Tag tag__, const Address *ad__, ResourcePtr content__) :
    content_(content__),
    tag_(tag__),
    address_(ad__) {
    ;
}

Packet::StreamBuffer Packet::get_data_streambuf() {
    std::stringstream ofs;
    boost::archive::text_oarchive oa(ofs);
    oa << *this;
    return ofs.str();
}

