#include <sstream>
#include "shared/Packet.hpp"
#include <boost/shared_ptr.hpp>
#include <boost/archive/text_oarchive.hpp>

Packet::Packet(Resource *content__, Tag tag__, Address ad__) :
    content_(content__),
    tag_(tag__),
    address_(ad__) {
    ;
}

Packet::Packet(ResourcePtr content__, Tag tag__, Address ad__) :
    content_(content__),
    tag_(tag__),
    address_(ad__) {
    ;
}

//Packet::StreamBuffer Packet::get_data_streambuf() { // TODO do poprawienia, kiedy będzie znany typ StreamBuffer
//    std::stringstream ofs;
//    boost::archive::text_oarchive oa(ofs);
//    oa << *this;
//    return ofs.str(); // ten return chyba nie ma sensu
//}

const Packet::Address &Packet::get_address() const {
    return address_;
}

Packet::Tag Packet::get_tag() {
    return tag_;
}
