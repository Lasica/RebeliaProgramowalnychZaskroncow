#ifndef CLIENTLISTRAW_H
#define CLIENTLISTRAW_H

#include <boost/serialization/base_object.hpp>

struct ClientListRaw {
    friend class boost::serialization::access;
  private:
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
    }
};

#endif // CLIENTLISTRAW_H
