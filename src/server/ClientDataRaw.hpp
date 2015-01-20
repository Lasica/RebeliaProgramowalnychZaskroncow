#ifndef CLIENTDATARAW_H
#define CLIENTDATARAW_H
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/export.hpp>

#include "shared/typedefinitions.hpp"
#include "shared/Resource.hpp"

/*!
* ClientState reprezentuje stan (miejsce), w którym obecnie jest klient - np. w grze.
*/

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
const ClientID UNINITIALISED_ID = std::numeric_limits<ClientID>::max();

/*!
*   To klasa zawierająca dane klienta. Jest klasą bazową dla Client.
*   To obiekty tej klasy są serializowane i przesyłane - dlatego jest oddzielona od Clienta i ma wszystkie pola public.
*/

struct ClientDataRaw : public Resource {

    ClientDataRaw() : clientID_(UNINITIALISED_ID) { } //!konstruktor dla boost::serialization
    ClientDataRaw(ClientID clientID, std::string nickname, ClientState state)
        : state_(state), clientID_(clientID), nickname_(nickname) { }

    mutable ClientState     state_;
    const ClientID          clientID_;   //! unikalne ID dla każdego gracza
    std::string             nickname_;

    virtual Tag get_tag() { return Resource::CLIENT_DATA; }
    virtual std::string show_content() {
        return "Client:" + std::to_string(clientID_) + ";" + nickname_ + ";(" + \
               std::to_string(state_.location) + "," + std::to_string(state_.locationIdentifier) + ")";
    }

  private:
    friend class boost::serialization::access;
    template<typename Archive>
    void serialize(Archive &ar, const unsigned int /*version*/) {   //! metoda dla boost::serialization do (de)serializacji obiektów
        ar &boost::serialization::base_object<Resource>(*this);
        ar &const_cast<ClientID &>(clientID_);
        ar &state_;
        ar &nickname_;
    }
};

#endif // CLIENTDATARAW_H
