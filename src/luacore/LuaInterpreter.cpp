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
    registerFunctions();
}

LuaInterpreter::~LuaInterpreter() {
    lua_close(state_);
}


int LuaInterpreter::load_settings(std::string to_interprete) {
    luaL_dostring(state_, to_interprete.c_str());
    return 0;// err
}

void LuaInterpreter::set_settings( lua_State* L ) {
    /* Read resolution settings */
    lua_getglobal(L, "width");
    lua_getglobal(L, "height");
    if (!lua_isnumber(L,-1) or !lua_isnumber(L,-2))
        throw std::runtime_error("invalid configuration lua file, you must specify number values for width and height");
    map.map_resize((int)lua_tonumber(L, -2), (int)lua_tonumber(L,-1));
}

void LuaInterpreter::registerFunctions() {
    //lua_register(state_, "change_field", );
}
