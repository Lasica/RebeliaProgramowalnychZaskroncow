#ifndef PACKET_HPP
#define PACKET_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <boost/serialization/type_info_implementation.hpp> // header wymagany przez shared_ptr (bug w booscie, opisany w internecie)
#include <boost/shared_ptr.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/shared_ptr.hpp>   //implementacja serializacji boost::shared_ptr

#include "shared/Resource.hpp"
#include "server/Address.hpp"


class Packet {
  public:
    //! Enum będący flagą stanowiącą podstawę komunikacji w naszym systemie
    /**
     * Ten enum moze urosnac duzy, poniewaz do kazdej dodanej funkcjonalnosci,
     * bedzie nowy tag pakietu.
     */
    enum Tag {
        UPDATED_RESOURCE,           //!< dane aktualizacyjne dla klienta, mozna rozpoznac zawartosc po tagu Resource
        REMOVE_RESOURCE,            //!< dane aktualizacyjne dla klienta, mozna rozpoznac zawartosc po tagu Resource
        REGISTER_REQUEST,           //!< w srodku pakietu Handshake przedstawiajacy dane o kliencie.
        CHAT_ENTRY_MESSAGE_REQUEST, //!< prosba o nadanie wiadomosci czatu
        GAMEROOM_CREATE_REQUEST,    //!< prosba o stworzenie nowego pokoju
        GAMEROOM_JOIN_REQUEST,      //!< prosba o dolaczenie do pokoju
        GAMEROOM_LEAVE_REQUEST,     //!< prosba o opuszczenie pokoju
        GAMEROOM_UPDATE_REQUEST,    //!< prosba o zmiane ustawien pokoju (np. ustawien gry dla hosta, a dla gracza wyrazenie gotowosci)
        GAMEROOM_START_REQUEST,     //!< prosba o rozpoczecie rozgrywki
        GAME_START_FAILURE_INFO,    //!< informacja dla klienta o niespelnionym rzadaniu, np. z powodu niegotowosci wszystkich graczy
        SYNCHRONISE_REQUEST,        //!< prosba o wyslanie wszystkich zasobow... podejrzewam, że mozna sie bez tego obyc i zamiast tego zrobic timeouty
        CLOCK_SYNCHRONISE,          //!< prosba o okreslenie czasu wzgledem serwera (sluzy tez do obliczenia round trip time)
        GAME_STATE,                 //!< pakiet zawierajacy stan rozgrywki - do przekierowania dla konkretnej instancji gry
        GAME_ACTION,                //!< byc moze sie przyda?
        KEEP_ALIVE                  //!< ping! do ustalenia czy ktos stracil polaczenie.
    };
    typedef std::string StreamBuffer;

    //! boost::serialization potrzebuje bezparametrowego konstruktora, można go przenieść do "private"
    Packet() { }
    Packet(Tag tag__, const Address* ad__=nullptr, Resource *content__=nullptr);
    Packet(Tag tag__, const Address* ad__, ResourcePtr content__=nullptr);

    friend class boost::serialization::access;
    //! Serializacja Pakietu dotyczy tagu pakietu i zawartości (wskaźnika na Resource)
    template<class Archive>
    void serialize(Archive &ar, const unsigned int) {
        ar &content_;
        ar &tag_;
    }

    StreamBuffer get_data_streambuf();

    const Address*  get_address() const {
        return address_;
    }
    Tag             get_tag()     const {
        return tag_;
    }
    ResourcePtr     get_content() const {
        return content_;
    }

    std::string show_resource_content() {
        return content_->show_content();
    }

  private:
    ResourcePtr content_;
    Tag tag_;
    const Address *address_;   // czy address jest potrzebny w pakiecie? - TAK!
};

#endif //PACKET_HPP

