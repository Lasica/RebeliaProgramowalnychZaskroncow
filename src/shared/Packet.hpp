#ifndef PACKET_HPP
#define PACKET_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <boost/serialization/type_info_implementation.hpp> // header wymagany przez shared_ptr (bug w booscie, opisany w internecie)
#include <boost/shared_ptr.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/shared_ptr.hpp>   //implementacja serializacji boost::shared_ptr
#include <shared/Resource.h>

#include "server/Address.hpp"


class Packet {
  public:
    // dziala, tylko konsekwencja umieszczenia go w klasie jest odnoszenie sie poprzez Packet::RESOURCE, itd.
    /*
     * Ten enum moze urosnac duzy, poniewaz do kazdej dodanej funkcjonalnosci,
     * bedzie nowy tag pakietu - w przyszlosci mozna sie zastanowic jak to zautomatyzowac.
     */
    enum Tag {
        RESOURCE,
        CONNECTION_END,
        CONNECTION_BEGIN
    };
    typedef std::string StreamBuffer;

    // boost::serialization potrzebuje bezparametrowego konstruktora, można go przenieść do "private"
    Packet() { }
    Packet(Tag tag__, Address ad__, Resource *content__=nullptr);
    Packet(Tag tag__, Address ad__, ResourcePtr content__=nullptr);

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int) {
        ar &content_;   // serializacja obiektu pokazywanego przez shared_ptr jest teraz prosta
        ar &tag_;
        ar &address_;
    }

    //TODO - tego moze nie byc, poniewaz Pakiet ma metode serialize, lecz poki co niech zostanie
    StreamBuffer get_data_streambuf();


    // !!! uwaga - inna metoda o nazwie get_tag() istnieje w Resource
    const Address&  get_address() const { return address_;  }
    Tag             get_tag()     const { return tag_;      }
    ResourcePtr     get_content() const { return content_;  }

    std::string show_resource_content() {
        return content_->show_content();
    }

  private:
    ResourcePtr content_;
    Tag tag_;
    Address address_;   // czy address jest potrzebny w pakiecie? - TAK!
};

#endif //PACKET_HPP

