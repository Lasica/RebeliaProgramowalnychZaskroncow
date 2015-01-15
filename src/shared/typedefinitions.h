#ifndef _TYPEDEFINITIONS_
#define _TYPEDEFINITIONS_
#include <queue>
#include <boost/shared_ptr.hpp>

class Packet;
typedef std::queue<Packet> PacketQueue;
    typedef unsigned int       ClientID;
    typedef int AddressIP;
    typedef short int AddressPort;

class Client;
typedef boost::shared_ptr<Client> ClientPtr;

typedef int GameRoomID;

#endif
