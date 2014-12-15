#ifndef GAMEROOM_H
#define GAMEROOM_H

#include "Resource.h"
#include "Observer.h"
#include "GameRoomRaw.h"

class GameRoom : public Resource, protected GameRoomRaw {
  public:
    /*
     * obiekty: ustawienia (parsowalne na lua):
     * dla przykladu: mapa, predkosci wezy,
     * stan: liczba graczy, maksymalna liczba graczy, lista graczy w pokoju, czy wystartowal czy nie
     * int: id_pokoju
     * string: nazwa gameroomu
     */
    GameRoom();
    ~GameRoom();
};

#endif // GAMEROOM_H
