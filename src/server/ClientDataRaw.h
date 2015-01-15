#ifndef CLIENTDATARAW_H
#define CLIENTDATARAW_H
#include <boost/serialization/base_object.hpp>
//odkomentować tego includa, jeśli ClientDataRaw ma dziedziczyć po Resource
//#include <boost/serialization/export.hpp>

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include "shared/typedefinitions.h"
#include "shared/Resource.h"


struct ClientState {
    enum Location { LOBBY, GAMEROOM, GAME };
    Location location;
    int locationIdentifier;

    ClientState(Location l, int lIdentifier) : location(l), locationIdentifier(lIdentifier) { } //for the purpose of GameRoom methods
    ClientState() { }
private:
    friend class boost::serialization::access;
    template<typename Archive>
    void serialize(Archive & ar, const unsigned int /*version*/) {
        ar & location;
        ar & locationIdentifier;
    }
};


//poniższe 2 linijki do odkomentowania, jeśli ClientDataRaw ma dziedziczyć po Resource
//struct ClientDataRaw;
//BOOST_CLASS_EXPORT(ClientDataRaw);

//TODO: serialization
struct ClientDataRaw /* :  public Resource */  {
    // TODO: W klasie Client lub tutaj dodać inicjację ClientID_ z jakiegoś licznika
    ClientDataRaw(ClientState state, ClientID clientID) : state_(state), clientID_(clientID) { }
    ClientState state_;
    const ClientID clientID_;   //unique ID for every player

    //konstruktor dla serializacji
    ClientDataRaw() : clientID_(-1) { }
private:
    friend class boost::serialization::access;
    template<typename Archive>
    void serialize(Archive & ar, const unsigned int /*version*/) {
        ar & state_;
        ar & const_cast<ClientID&>(clientID_);  //clientID_ jest stały, więc trzeba go serializować tak
    }

};

#endif // CLIENTDATARAW_H
