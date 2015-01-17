#ifndef GAMEROOMRAW_H
#define GAMEROOMRAW_H

#include <boost/serialization/base_object.hpp>
#include <boost/serialization/export.hpp>       //makro BOOST_CLASS_EXPORT
#include <boost/serialization/list.hpp>         // dla serializacji std::list<>

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include "shared/Resource.hpp"
#include <string>
#include <list>

struct GameRoomRaw;
//BOOST_CLASS_EXPORT(GameRoomRaw)
BOOST_CLASS_EXPORT_KEY(GameRoomRaw)

// Powinna tez zawierac liczbe graczy.
struct GameRoomRaw : public Resource {

    GameRoomRaw() { }
    GameRoomRaw(std::string name) : gameRoomName(name) { }
    virtual ~GameRoomRaw() { }

    std::string             gameRoomName;
    std::list<std::string>  playersNames;    // nicki wszystkich graczy w tym pokoju

    virtual Tag get_tag() {
        return GAMEROOM;
    }
    // WTF, co sie tu dzieje?
    virtual std::string show_content() {
        return ("** GameRoomRaw **, gameRoomName==" + gameRoomName + std::string([this]()->std::string { std::string temp(""); for(auto a : playersNames) temp += a; return temp;}())
                + "\n");
    }

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int) {
        ar &boost::serialization::base_object<Resource>(*this);
        ar &gameRoomName;
        ar &playersNames;
    }
};

#endif // GAMEROOMRAW_H
