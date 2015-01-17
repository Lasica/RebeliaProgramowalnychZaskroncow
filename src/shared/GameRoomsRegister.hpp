#ifndef GAMEROOMSREGISTER_HPP
#define GAMEROOMSREGISTER_HPP

#include "shared/typedefinitions.hpp"
#include "shared/GameRoom.hpp"
#include <boost/shared_ptr.hpp>
#include <map>


class GameRoomsRegister : public Observer {
public:
    GameRoomsRegister();
    virtual ~GameRoomsRegister();
    GameRoomPtr add_game_room(ClientID host, std::string name);
    void remove_game_room(GameRoomID id);

    GameRoomPtr look_up_with_id(GameRoomID id);

    unsigned int get_size();

private:
    GameRoomsRegister(GameRoomsRegister& copy) = delete;
    GameRoomsRegister &operator=(GameRoomsRegister &grr) = delete;

    std::map<GameRoomID, GameRoomPtr> game_rooms_;
};

#endif // GAMEROOMSREGISTER_HPP
