#ifndef CLIENTDATARAW_H
#define CLIENTDATARAW_H
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/export.hpp>

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include "shared/typedefinitions.hpp"
#include "shared/Resource.hpp"


struct ClientState {
    enum Location { LOBBY, GAMEROOM, GAME };
    Location location;
    int locationIdentifier;

    ClientState(Location l = LOBBY, int lIdentifier = 0) : location(l), locationIdentifier(lIdentifier) { }

  private:
    friend class boost::serialization::access;
    template<typename Archive>
    void serialize(Archive &ar, const unsigned int /*version*/) {
        ar &location;
        ar &locationIdentifier;
    }
};


struct ClientDataRaw;
const ClientID UNINITIALISED_ID = -1;

struct ClientDataRaw : public Resource {
    //konstruktor dla serializacji
    ClientDataRaw() : clientID_(UNINITIALISED_ID) { }
    ClientDataRaw(ClientID clientID, std::string nickname, ClientState state)
        : state_(state), clientID_(clientID), nickname_(nickname) { }

    mutable ClientState     state_;
    const ClientID          clientID_;   //unique ID for every player
    std::string             nickname_;

    virtual Tag get_tag() { return Resource::CLIENT_DATA; }
    virtual std::string show_content() {
        return "Client:" + std::to_string(clientID_) + ";" + nickname_ + ";(" + \
               std::to_string(state_.location) + "," + std::to_string(state_.locationIdentifier) + ")";
    }

  private:
    friend class boost::serialization::access;
    template<typename Archive>
    void serialize(Archive &ar, const unsigned int /*version*/) {
        ar &boost::serialization::base_object<Resource>(*this);
        ar &const_cast<ClientID &>(clientID_);
        ar &state_;
        ar &nickname_;
    }

};

#endif // CLIENTDATARAW_H
