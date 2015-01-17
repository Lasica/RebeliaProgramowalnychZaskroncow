/*
 * Written by Artur Dobrogowski.
 * Copyright 2014
 */

#include "luacore/LuaInterpreter.hpp"

LuaInterpreter::LuaInterpreter() {
    // create new Lua state
    state_ = luaL_newstate();

    // load Lua libraries
    static const luaL_Reg lualibs[] = {
        { "base", luaopen_base },
        { NULL, NULL}
    };

    const luaL_Reg *lib = lualibs;

    for(; lib->func != NULL; lib++) {
        lib->func(state_);
        lua_settop(state_, 0);
    }

    //lua_register(state_, "wall", createWall);
    registerFunctions();
}

LuaInterpreter::~LuaInterpreter() {
    // close the Lua state
    lua_close(state_);
    //delete state_;
}


int LuaInterpreter::interprete(QString to_interprete) {
    char *mesg;
    mesg = new char[to_interprete.size() + 1];

    for(int i = 0; i < to_interprete.size(); ++i)
        mesg[i] = to_interprete[i].toAscii();

    mesg[to_interprete.size()] = '\0';
    //addLogEntry(to_interprete);
    luaL_dostring(state_, mesg);
    /*int err = luaL_loadbuffer(state_, mesg, to_interprete.size()+1, "line")
    or lua_pcall(state_, 0, 0, 0);*/
    delete [] mesg;
    return 0;// err
}


void LuaInterpreter::registerFunctions() {
    lua_register(state_, "wall", createWall);
}
