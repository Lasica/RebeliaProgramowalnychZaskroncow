#ifndef ADDRESS_HPP
#define ADDRESS_HPP

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

#include <string>
#include <iostream>

struct Address {
    typedef int IP;

    IP ip;     // do zmiany później
    short int port;
    std::string nickname; // potrzebne?


    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int) {
        ar & ip;
        ar & port;
        ar & nickname;
    }
};

std::ostream& operator<<(std::ostream &o, const Address &a);

#endif // ADDRESS_HPP
