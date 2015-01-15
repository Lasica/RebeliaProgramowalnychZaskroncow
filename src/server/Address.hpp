#ifndef ADDRESS_HPP
#define ADDRESS_HPP

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include "shared/typedefinitions.h"

#include <string>
#include <iostream>

struct Address {
    AddressIP ip;     // do zmiany później
    AddressPort port;
    Address(AddressIP Ip, AddressPort Port) : ip(Ip), port(Port) { }

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int /* version */) {
        ar & ip;
        ar & port;
    }

    bool operator<(const Address &latter) const;

    Address() : ip(0), port(1) { }  // konstruktor bezparametrowy przydaje się m.in w testach i dla konstruktora bezparametrowego Packetu
};

std::ostream& operator<<(std::ostream &o, const Address &a);

#endif // ADDRESS_HPP
