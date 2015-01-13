#ifndef CLIENTDATARAW_H
#define CLIENTDATARAW_H
#include "shared/typedefinitions.h"

struct ClientState {
    enum Location { LOBBY, GAMEROOM, GAME };
    Location location;
    int locationIdentifier;

    ClientState(Location l, int lIdentifier) : location(l), locationIdentifier(lIdentifier) { } //for the purpose of GameRoom methods
};

//TODO: serialization
struct ClientDataRaw {
    ClientDataRaw(ClientState state, ClientID clientID) : state_(state), clientID_(clientID) { }
    ClientState state_;
    const ClientID clientID_;   //unique ID for every player
};

#endif // CLIENTDATARAW_H
