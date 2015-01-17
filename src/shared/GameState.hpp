#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "shared/Resource.hpp"

class GameState : public Resource
{
public:
    virtual std::string show_content();
    virtual Resource::Tag get_tag();
};

#endif // GAMESTATE_H
