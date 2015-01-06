#ifndef ADDRESS_HPP
#define ADDRESS_HPP

#include <string>
#include <iostream>

struct Address {
    typedef int IP;

    IP ip;     // do zmiany później
    short int port;
    std::string nickname; // potrzebne?    
};

std::ostream& operator<<(std::ostream &o, const Address &a);

#endif // ADDRESS_HPP
