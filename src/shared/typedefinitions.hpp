#ifndef _TYPEDEFINITIONS_
#define _TYPEDEFINITIONS_
#include <queue>
#include <boost/shared_ptr.hpp>
#include <string>
#include <set>

/*
 * Nie nalezy includowac klas ktore sa tu uzywane do definicji typu,
 * poniewaz nie udaloby sie rozwiazac tych wszystkich zaleznosci.
 * Nalezy je tylko deklarowac.
 */
class Packet;
class Client;
class TcpConnection;
class Resource;


typedef std::set<Client>::iterator          ClientIt;
typedef std::string                         AddressIP;
typedef std::queue<Packet>                  PacketQueue;
typedef boost::shared_ptr<TcpConnection>    TcpPointer;
typedef boost::shared_ptr<Client>           ClientPtr;
typedef boost::shared_ptr<Resource>         ResourcePtr;
typedef int                                 GameRoomID;
typedef unsigned int                        ClientID;
typedef unsigned short                      AddressPort;

extern const ClientID INVALID_CLIENT_ID;
#endif
