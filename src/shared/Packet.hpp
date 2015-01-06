#ifndef PACKET_HPP
#define PACKET_HPP

#include <iostream>
//#include <streambuf>
#include <string>
#include <sstream>
#include <memory>
#include <boost/serialization/base_object.hpp>
#include <shared/Resource.h>

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
        //ar & content_;    //docelowo zamiast data_
        //ar & address.nickname;      //może nickname przenieść z powrotem do Packet?
    }

    //TODO
    StreamBuffer get_data_streambuf();
    const Address& get_address() const;

    //na potrzeby testów - niekoniecznie jest potrzebne dla programu
    std::string get_data_string();
    PacketTag get_tag();

private:

    // problem: co się stanie z obiektem, do którego odwołuje się referencja po usunięciu tego, konkretnego pakietu?
    //Resource& content_;

    // wskazywany obiekt zostaje usunięty wraz z pakietem
    // trzeba używać odpowiedniej metody do inicjalizowania tego wskaźnika (std::move(...)?)
    //std::unique_ptr<Resource> content_;

    std::string data_;
    PacketTag tag_;

    Address address_;
};

#endif //PACKET_HPP

