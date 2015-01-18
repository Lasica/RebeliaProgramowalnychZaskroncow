#include "luacore/LuaInterpreter.hpp"
LuaInterpreter::LuaInterpreter() {
    //std::cout << "konstruktor\n";
    // create new Lua state
    state_ = luaL_newstate();

    // load Lua libraries
//     static const luaL_Reg lualibs[] = {
//         { "base", luaopen_base },
//         { NULL, NULL}
//     };
//     const luaL_Reg *lib = lualibs;
//
//     for(; lib->func != NULL; lib++) {
//         lib->func(state_);
//         lua_settop(state_, 0);
//     }
//     registerFunctions();
}

LuaInterpreter::~LuaInterpreter() {
    //std::cout << "destruktor" << std::endl;
    lua_close(state_);
}


void LuaInterpreter::load_settings(const char * to_interprete) {
    //std::cout << "load_settings\n";
    luaL_dostring(state_, to_interprete);
}

void LuaInterpreter::set_settings( ) {
    //std::cout << "set_settings\n";
    /* Read resolution settings */
    lua_getglobal(state_, "width");
    lua_getglobal(state_, "height");
    if (!lua_isnumber(state_,-1) or !lua_isnumber(state_,-2))
        throw std::runtime_error("invalid configuration lua file, you must specify number values for width and height");
    //std::cout << (int)lua_tonumber(state_, -2) << " " << (int)lua_tonumber(state_,-1) << std::endl;
    map.map_resize((int)lua_tonumber(state_, -2), (int)lua_tonumber(state_,-1));
}

void LuaInterpreter::registerFunctions() {
    //lua_register(state_, "change_field", );
}
