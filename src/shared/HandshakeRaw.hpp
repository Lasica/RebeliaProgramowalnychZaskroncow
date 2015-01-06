/**
 * Handshake objects are used to establish a new connection between a client and the server.
 * They contain information about client willing to connect to the server.
 */

#ifndef HANDSHAKE_RAW_HPP
#define HANDSHAKE_RAW_HPP

#include "shared/Resource.h"
#include "server/Address.hpp"
#include "shared/Packet.hpp"

class HandshakeRaw : public Resource {
public:
    HandshakeRaw(Address ad) : address_(ad) { ; }
    ~HandshakeRaw() { ; }

    const static  PacketTag idTag_;

private:
    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int) {
        ar & address_;
    }

    Address address_;
};

const PacketTag HandshakeRaw::idTag_ = CONNECTION_BEGIN;

#endif //HANDSHAKE_RAW_HPP
