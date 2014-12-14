#ifndef GAMEROOM_H
#define GAMEROOM_H

#include "Resource.h"
#include "Observer.h"
#include <boost/serialization/base_object.hpp>

class GameRoom : public Resource {
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
  private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) const {
    }
};

#endif // GAMEROOM_H
