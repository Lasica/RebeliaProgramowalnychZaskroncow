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
    Packet() { ; }
    Packet(std::string str);

    typedef std::string StreamBuffer;
    typedef int Address;

    friend class boost::serialization::access;
    template<class Archive>     // dla serializacji w konstruktorze potrzeba znać Archive
    void serialize(Archive & ar, const unsigned int /*version*/)
    {
        ar & data_;
        ar & sender_;
    }

    StreamBuffer get_data_streambuf();
    const Address& get_address() const;

    //na potrzeby testów - niekoniecznie jest potrzebne dla programu
    std::string get_data_string();

private:

    std::string data_;

    Address sender_;  // jaki typ?
};

#endif //PACKET_HPP
