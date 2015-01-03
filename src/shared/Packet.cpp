//#include <streambuf>
#include "shared/Packet.hpp"
#include <boost/archive/text_oarchive.hpp>

Packet::Packet(std::string str) :
    data_(str) {
    ;
}

Packet::StreamBuffer Packet::get_data_streambuf() { // TODO do poprawienia, kiedy będzie znany typ StreamBuffer
    Packet::StreamBuffer x;
    std::stringstream ofs;
    boost::archive::text_oarchive oa(ofs);
    oa << *this;
    ofs >> x;
    return x;
}

const Packet::Address& Packet::get_address() const
{
    return sender_;
}

std::string Packet::get_data_string() {
    return data_;
}
