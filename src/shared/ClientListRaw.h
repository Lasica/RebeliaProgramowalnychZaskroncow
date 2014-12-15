#ifndef CLIENTLISTRAW_H
#define CLIENTLISTRAW_H

#include <boost/serialization/base_object.hpp>

struct ClientListRaw {
    friend class boost::serialization::access;
};

#endif // CLIENTLISTRAW_H
