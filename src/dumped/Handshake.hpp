/**
 * Handshake objects are used to establish a new connection between a client and the server.
 * They contain information about client willing to connect to the server.
 */

#ifndef HANDSHAKE_HPP
#define HANDSHAKE_HPP

#include "shared/HandshakeRaw.hpp"
#include "server/Address.hpp"

class Handshake : protected HandshakeRaw {
  public:
    Handshake(Address ad);
    ~Handshake();

};


#endif //HANDSHAKE_HPP
