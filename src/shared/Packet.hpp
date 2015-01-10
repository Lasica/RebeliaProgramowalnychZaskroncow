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
    //TODO: zrobić "coś", żeby kod się kompilował po podaniu do konstruktora enumu zamiast przypisanego mu inta...
    enum Tag { RESOURCE = 1, CONNECTION_END = 2, CONNECTION_BEGIN = 3 };
    typedef boost::shared_ptr<Resource> ResourcePtr;
    // TODO: usunąć ten typedef - adresem będzie struktura typu Address
    typedef int Address;
    typedef std::string StreamBuffer;

    Packet() { ; }
    Packet(Resource* content__, Tag tag__, Address ad__);
    Packet(ResourcePtr content__, Tag tag__, Address ad__);

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int)
    {
        ar & content_;  // serializacja obiektu pokazywanego przez scoped_ptr jest teraz banalnie prosta
        ar & tag_;
        ar & address_;
    }

    //TODO
    //StreamBuffer get_data_streambuf();
    const Address& get_address() const;

    // !!! uwaga - inna metoda o nazwie get_tag() istnieje w Resource
    Tag get_tag();

    std::string show_resource_content(){ return content_->show_content();}

private:
    ResourcePtr content_;
    Tag tag_;
    Address address_;
};

#endif //PACKET_HPP

