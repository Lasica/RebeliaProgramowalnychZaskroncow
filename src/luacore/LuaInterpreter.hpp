#ifndef LUAINTERPRETER_H
#define LUAINTERPRETER_H

#include <thread>
#include <lua.hpp>
#include "shared/GameSettings.hpp"
class LuaInterpreter : protected GameSettings {
public:
    void set_settings(lua_State *L);
    int load_settings(std::string);
    LuaInterpreter();
    ~LuaInterpreter();
    void registerFunctions();
private:
    lua_State *state_;
    const luaL_Reg *libs;
};

#endif // LUAINTERPRETER_H
