#ifndef GAMEROOMSREGISTER_HPP
#define GAMEROOMSREGISTER_HPP

#include <boost/thread/shared_mutex.hpp>
#include "shared/typedefinitions.hpp"
#include "shared/GameRoom.hpp"
#include <boost/shared_ptr.hpp>
#include <map>
#include "shared/Subject.hpp"

/*!
 *  Rejestr pokojów gry - służy do zarządzania pokojami gry na serwerze.
 *  Pozwala na dodawanie, usuwanie pokojów.
 */


class GameRoomsRegister : public Observer, public Subject {
public:
    GameRoomsRegister();
    virtual ~GameRoomsRegister();
    GameRoomPtr add_game_room(ClientID host, std::string name); //! dodawanie nowego pokoju do rejestru
    void remove_game_room(GameRoomID id);                       //! usuwanie z serwera pokoju o zadanym id

    GameRoomPtr look_up_with_id(GameRoomID id);                 //! wyszukiwanie pokoju o zadanym id

    unsigned int get_size();
    
    void notify(Resource*,const Packet::Tag*);
private:
    GameRoomsRegister(GameRoomsRegister& copy) = delete;
    GameRoomsRegister &operator=(GameRoomsRegister &grr) = delete;

    std::map<GameRoomID, GameRoomPtr> game_rooms_;
    mutable boost::shared_mutex            access_;

};

#endif // GAMEROOMSREGISTER_HPP
