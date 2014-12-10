/*
 * Written by Artur Dobrogowski.
 * Copyright 2014
 */

#ifndef LUAINTERPRETER_H
#define LUAINTERPRETER_H

#include <thread>
#include <lua.hpp>
#include <QtCore/QString>

class LuaInterpreter {
    lua_State *state_;
    const luaL_Reg *libs;
  public:
    int interprete(QString);
    LuaInterpreter();
    ~LuaInterpreter();
    void registerFunctions();
};

#endif // LUAINTERPRETER_H
