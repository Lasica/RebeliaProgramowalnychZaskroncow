#ifndef GAMEROOMLIST_H
#define GAMEROOMLIST_H

#include "Observer.h"
#include "Resource.h"
#include "GameRoomListRaw.h"

class GameRoomList : public Observer, public Resource, protected GameRoomListRaw {
  private:
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) const {
    }
};

#endif // GAMEROOMLIST_H
