#ifndef GAMEROOMLIST_H
#define GAMEROOMLIST_H

#include "Observer.hpp"
#include "Resource.hpp"
#include "GameRoomListRaw.hpp"

class GameRoomList : public Observer, public Resource, protected GameRoomListRaw {
  private:
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) const {
    }
};

#endif // GAMEROOMLIST_H
