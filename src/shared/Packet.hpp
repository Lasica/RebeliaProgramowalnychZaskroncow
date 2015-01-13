#ifndef PACKET_HPP
#define PACKET_HPP

#include <iostream>
#include <string>
#include <boost/serialization/type_info_implementation.hpp> // header wymagany przez shared_ptr (bug w booscie, opisany w internecie)
#include <boost/shared_ptr.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/shared_ptr.hpp>   //implementacja serializacji boost::shared_ptr
#include <shared/Resource.h>

#include "server/Address.hpp"


class Packet {
public:
    // dziala, tylko konsekwencja umieszczenia go w klasie jest odnoszenie sie poprzez Packet::RESOURCE, itd.
    enum Tag { RESOURCE, CONNECTION_END, CONNECTION_BEGIN };
    typedef boost::shared_ptr<Resource> ResourcePtr;
    // TODO: usunąć ten typedef - adresem będzie struktura typu Address
    //typedef int Address;
    typedef std::string StreamBuffer;

    // boost::serialization potrzebuje bezparametrowego konstruktora, można go przenieść do "private"
    Packet() { }
    Packet(Resource* content__, Tag tag__, Address ad__);
    Packet(ResourcePtr content__, Tag tag__, Address ad__);

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int)
    {
        ar & content_;  // serializacja obiektu pokazywanego przez shared_ptr jest teraz prosta
        ar & tag_;
        ar & address_;  //
    }

    //TODO - tego moze nie byc, poniewaz Pakiet ma metode serialize.
    StreamBuffer get_data_streambuf();
    const Address& get_address() const;

    // !!! uwaga - inna metoda o nazwie get_tag() istnieje w Resource
    Tag get_tag();

    std::string show_resource_content(){ return content_->show_content();}

private:
    ResourcePtr content_;
    Tag tag_;
    Address address_;   // czy address jest potrzebny w pakiecie?
};

#endif //PACKET_HPP

