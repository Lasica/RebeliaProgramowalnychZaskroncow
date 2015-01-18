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
class ClientDataRaw;
class TcpConnection;
class Resource;
class PacketQueueAdapter;


class GameRoom;


typedef std::string                         AddressIP;
typedef PacketQueueAdapter                  PacketQueue;
typedef boost::shared_ptr<TcpConnection>    TcpPointer;
typedef boost::shared_ptr<Client>           ClientPtr;
typedef boost::shared_ptr<Resource>         ResourcePtr;
typedef unsigned int                        GameRoomID;
typedef unsigned int                        ClientID;
typedef unsigned short                      AddressPort;
typedef boost::shared_ptr<GameRoom>         GameRoomPtr;
typedef std::set<ClientPtr>::iterator     ClientIt;

extern const ClientID INVALID_CLIENT_ID;
extern const AddressPort PORT;
#endif
