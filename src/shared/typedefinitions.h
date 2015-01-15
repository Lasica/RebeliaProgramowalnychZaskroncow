#ifndef _TYPEDEFINITIONS_
#define _TYPEDEFINITIONS_
#include <queue>
#include <boost/shared_ptr.hpp>
#include <string>

class Packet;
class Client;
class TcpConnection;

typedef std::queue<Packet>                  PacketQueue;
typedef unsigned int                        ClientID;
typedef std::string                         AddressIP;
typedef unsigned short                      AddressPort;
typedef boost::shared_ptr<TcpConnection>    TcpPointer;
typedef boost::shared_ptr<Client>           ClientPtr;
typedef int                                 GameRoomID;

#endif
