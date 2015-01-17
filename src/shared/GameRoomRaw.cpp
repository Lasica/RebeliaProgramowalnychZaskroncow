#include "typedefinitions.hpp"
#include "shared/GameRoomRaw.hpp"

#include <boost/serialization/base_object.hpp>
#include <boost/serialization/export.hpp>       //makro BOOST_CLASS_EXPORT
#include <boost/serialization/list.hpp>         // dla serializacji std::list<>

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

// czy to potrzebne?
class GameRoomRaw;
BOOST_CLASS_EXPORT_IMPLEMENT(GameRoomRaw)

GameRoomID GameRoomRaw::gameRoomCounter = 1; //nie wiem czy nie zepsulem i nie wyrzucilem czegos co tu bylo
// ale inkrementator statyczny nie powinien być w RAW, tylko w GameRoom jak juz.

