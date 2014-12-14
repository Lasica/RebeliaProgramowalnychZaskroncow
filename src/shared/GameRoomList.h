#ifndef GAMEROOMLIST_H
#define GAMEROOMLIST_H

#include "Observer.h"
#include "Resource.h"
#include <boost/serialization/base_object.hpp>

class GameRoomList : public Observer, public Resource {
  private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) const {
    }
};

#endif // GAMEROOMLIST_H
