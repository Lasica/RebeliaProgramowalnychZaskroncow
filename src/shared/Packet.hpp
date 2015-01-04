#ifndef PACKET_HPP
#define PACKET_HPP

#include <iostream>
//#include <streambuf>
#include <string>
#include <sstream>
#include <boost/serialization/base_object.hpp>


enum PacketTag { CHAT_ENTRY, GAME_STATE, CONNECTION_END, CONNECTION_BEGIN };

class Packet {
public:
    typedef int Address;
    typedef std::string StreamBuffer;

    Packet() { }
    Packet(std::string str, PacketTag tag, Address ad);


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
