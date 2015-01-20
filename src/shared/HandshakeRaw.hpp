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
#include "shared/Resource.hpp"
#include "server/Address.hpp"

struct HandshakeRaw;
BOOST_CLASS_EXPORT_KEY(HandshakeRaw)

struct HandshakeRaw : public Resource {

    HandshakeRaw(std::string nick) : nick_(nick) {
        ;
    }
    virtual ~HandshakeRaw() {
        ;
    }

    virtual Resource::Tag get_tag() {
        return Resource::HANDSHAKE;
    }

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int) {
        //serializacja klasy bazowej
        ar &boost::serialization::base_object<Resource>(*this);

        ar &nick_;
    }

    std::string nick_;

    // tylko dla testów
    virtual std::string show_content() {
        return ("** HandshakeRaw **, nick_==" + nick_ + "\n");
    }
};

#endif //HANDSHAKE_RAW_HPP
