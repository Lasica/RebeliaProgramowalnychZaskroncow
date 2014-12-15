#ifndef GAMEROOMRAW_H
#define GAMEROOMRAW_H

#include <boost/serialization/base_object.hpp>

struct GameRoomRaw {
    friend class boost::serialization::access;
  private:
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) const {
    }
};

#endif // GAMEROOMRAW_H
