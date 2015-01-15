#include "server/Address.hpp"

std::ostream &operator<<(std::ostream &o, const Address &a) {
    o << a.ip << ":" << std::to_string(a.port);
    return o;
}

bool Address::operator<(const Address &latter) const {
    if(ip == latter.ip)
        return port < latter.port;
    else
        return ip < latter.ip;
}

