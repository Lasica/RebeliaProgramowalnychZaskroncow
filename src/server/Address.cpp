#include "server/Address.hpp"

std::ostream& operator<<(std::ostream &o, const Address &a)
{
    o << a.nickname << ";" << std::to_string(a.ip) << ":" << std::to_string(a.port);
    return o;
}
