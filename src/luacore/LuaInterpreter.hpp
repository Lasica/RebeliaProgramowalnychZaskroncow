#ifndef LUAINTERPRETER_H
#define LUAINTERPRETER_H

#include <thread>
#include <lua.hpp>
#include "shared/GameSettings.hpp"
class LuaInterpreter : public GameSettings {
public:
    void set_settings();
    void load_settings(const char *);
    LuaInterpreter();
    ~LuaInterpreter();
    void registerFunctions();
private:
    LuaInterpreter(const LuaInterpreter &) = delete;
    LuaInterpreter& operator=(const LuaInterpreter &a) = delete;
    lua_State *state_;
    const luaL_Reg *libs;
};

#endif // LUAINTERPRETER_H
