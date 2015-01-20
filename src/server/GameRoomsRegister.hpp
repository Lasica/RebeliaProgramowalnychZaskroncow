#ifndef GAMEROOMSREGISTER_HPP
#define GAMEROOMSREGISTER_HPP

#include <boost/thread/shared_mutex.hpp>
#include "shared/typedefinitions.hpp"
#include "shared/GameRoom.hpp"
#include <boost/shared_ptr.hpp>
#include <map>
#include "shared/Subject.hpp"

class GameRoomsRegister : public Observer, public Subject {
public:
    GameRoomsRegister();
    virtual ~GameRoomsRegister();
    GameRoomPtr add_game_room(ClientID host, std::string name);
    void remove_game_room(GameRoomID id);
    //interfejs dla gracza: join(id),

    GameRoomPtr look_up_with_id(GameRoomID id);

    unsigned int get_size();
    
    void notify();
private:
    GameRoomsRegister(GameRoomsRegister& copy) = delete;
    GameRoomsRegister &operator=(GameRoomsRegister &grr) = delete;

    std::map<GameRoomID, GameRoomPtr> game_rooms_;
    mutable boost::shared_mutex            access_;

};

#endif // GAMEROOMSREGISTER_HPP
