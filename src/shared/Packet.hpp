#ifndef PACKET_HPP
#define PACKET_HPP

#include <iostream>
//#include <streambuf>
#include <string>
#include <boost/serialization/base_object.hpp>


enum PacketTag { CHAT_ENTRY, GAME_STATE };

class Packet {
public:
    Packet(std::string str);

    typedef int StreamBuffer;
    friend class boost::serialization::access;
    template<class Archive>     // dla serializacji w konstruktorze potrzeba znać Archive
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & data_;
        ar & sender_;
    }

    StreamBuffer get_data_streambuf();

private:

    std::string data_;

    typedef int Address;
    Address sender_;  // jaki typ?
};

#endif //PACKET_HPP
