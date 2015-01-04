#ifndef PACKET_HPP
#define PACKET_HPP

#include <iostream>
//#include <streambuf>
#include <string>
#include <sstream>
#include <boost/serialization/base_object.hpp>


enum PacketTag { CHAT_ENTRY, GAME_STATE };

class Packet {
public:
    Packet()   { ; }
    typedef int Address;
    Packet(std::string str, PacketTag tag, Address ad);

    typedef std::string StreamBuffer;

    friend class boost::serialization::access;
    template<class Archive>     // dla serializacji w konstruktorze potrzeba znać Archive
    void serialize(Archive & ar, const unsigned int /*version*/)
    {
        ar & data_;
        ar & tag_;
    }

    //TODO
    StreamBuffer get_data_streambuf();
    const Address& get_address() const;

    //na potrzeby testów - niekoniecznie jest potrzebne dla programu
    std::string get_data_string();
    PacketTag get_tag();

private:

    std::string data_;
    PacketTag tag_;

    Address address_;
};

#endif //PACKET_HPP
