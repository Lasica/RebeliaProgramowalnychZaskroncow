#ifndef GAMEROOMLISTRAW_H
#define GAMEROOMLISTRAW_H

#include <boost/serialization/base_object.hpp>

struct GameRoomListRaw {
    friend class boost::serialization::access;
  private:
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
    }
};

#endif // GAMEROOMLISTRAW_H
