/**
 * Handshake objects are used to establish a new connection between a client and the server.
 * They contain information about client willing to connect to the server.
 */

#ifndef HANDSHAKE_RAW_HPP
#define HANDSHAKE_RAW_HPP

#include <boost/serialization/base_object.hpp>
#include <boost/serialization/export.hpp>       //makro BOOST_CLASS_EXPORT

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

#include <string>
#include "shared/Resource.h"
#include "server/Address.hpp"

struct HandshakeRaw;
BOOST_CLASS_EXPORT(HandshakeRaw)

struct HandshakeRaw : public Resource {
    HandshakeRaw(Address ad=Address(0,0)) : address_(ad) { ; }
    virtual ~HandshakeRaw() { ; }

    virtual Resource::Tag get_tag() { return HANDSHAKE; }

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int) {
        //serializacja klasy bazowej
        ar & boost::serialization::base_object<Resource>(*this);

        ar & address_;
    }

    Address address_;


    // tylko dla testów
    virtual std::string show_content() { return ("** HandshakeRaw **, address.ip==" + std::to_string(address_.ip) + ", address.port==" + std::to_string(address_.port) + "\n"); }
};

#endif //HANDSHAKE_RAW_HPP
