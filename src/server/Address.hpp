#ifndef ADDRESS_HPP
#define ADDRESS_HPP

#include <string>

struct Address {
    typedef int IP;

    IP ip;     // do zmiany później
    short int port;
    std::string nickname; // potrzebne?    
};

#endif // ADDRESS_HPP
