#ifndef GAMEROOMRAW_H
#define GAMEROOMRAW_H

#include <boost/serialization/base_object.hpp>
#include <boost/serialization/export.hpp>       //makro BOOST_CLASS_EXPORT

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include "shared/Resource.h"
#include <string>
#include <list>

struct GameRoomRaw;
BOOST_CLASS_EXPORT(GameRoomRaw)


struct GameRoomRaw : public Resource {

    GameRoomRaw() {}
    ~GameRoomRaw() {}

    std::string gameRoomName;
    std::list<std::string> playersNames;

private:

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & boost::serialization::base_object<Resource>(*this);
        ar & gameRoomName;
    }
};

#endif // GAMEROOMRAW_H
