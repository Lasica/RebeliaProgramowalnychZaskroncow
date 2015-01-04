//#include <streambuf>
#include <sstream>
#include "shared/Packet.hpp"
#include <boost/archive/text_oarchive.hpp>

Packet::Packet(std::string str, PacketTag tag, Address ad) :
    data_(str),
    tag_(tag),
    address_(ad) {
    ;
}

// Uwaga! Wykomentowane linie w poniższej metodzie wywołują błędy!
Packet::StreamBuffer Packet::get_data_streambuf() { // TODO do poprawienia, kiedy będzie znany typ StreamBuffer
    Packet::StreamBuffer x;
    std::stringstream ofs;
//    boost::archive::text_oarchive oa(ofs);
//    oa << *this;
    ofs >> x;
    //return x;
    return "Packet::get_data_streambuf() here!";
}

const Packet::Address &Packet::get_address() const {
    return address_;
}

std::string Packet::get_data_string() {
    return data_;
}

PacketTag Packet::get_tag() {
    return tag_;
}
