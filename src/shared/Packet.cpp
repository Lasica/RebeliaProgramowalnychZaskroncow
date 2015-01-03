//#include <streambuf>
#include "shared/Packet.hpp"

Packet::Packet(std::string str) :
    data_(str) {
    ;
}

Packet::StreamBuffer Packet::get_data_streambuf() { //do poprawienia, kiedy będzie znany typ StreamBuffer

    return 15;
}
