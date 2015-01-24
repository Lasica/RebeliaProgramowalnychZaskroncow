#include "Address.hpp"
#include <string>
std::ostream &operator<<(std::ostream &o, const Address &a) {
    //o << a.ip << ":" << std::to_string(a.port);
    return o;
}

bool Address::operator<(const Address &latter) const {
    if(port == latter.port) // short int porty szybciej sie porownuje niz stringi IP
        return ip < latter.ip;
    else
        return port < latter.port;
}

