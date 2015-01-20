
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE "Przykladowy test"
#include <iostream>
#include <algorithm>
#include <thread>
#include <lua.hpp>

#include "luacore/LuaInterpreter.hpp"

#include <boost/test/unit_test.hpp> //VERY IMPORTANT - include this last

using namespace boost::unit_test;

BOOST_AUTO_TEST_SUITE( JakisBlokTestow )
BOOST_AUTO_TEST_CASE( JakisAtomowyTest ) {
    using namespace std;
//     lua_State *state_;
//     state_ = luaL_newstate();
//
//     // load Lua libraries
//     static const luaL_Reg lualibs[] = {
//         { "base", luaopen_base },
//         { NULL, NULL}
//     };
//     const luaL_Reg *lib = lualibs;
//     luaL_dostring(state_, "widtdsah=5;height=12;");
//     lua_getglobal(state_, "width");
//     lua_getglobal(state_, "height");
//     if (!lua_isnumber(state_,-1) or !lua_isnumber(state_,-2))
//         std::cout << "kurwa\n";
//     std::cout << (int)lua_tonumber(state_, -2) << " " << (int)lua_tonumber(state_,-1) << std::endl;
//     lua_close(state_);

  LuaInterpreter LI;// = new LuaInterpreter;
  BOOST_CHECK_THROW(LI.set_settings(), std::runtime_error);
  BOOST_CHECK_NO_THROW(LI.load_settings("width=15;height=12;"));
  BOOST_CHECK_NO_THROW(LI.set_settings());
  GameSettings gs = LI;
  BOOST_CHECK_EQUAL(gs.map.height, 12);
  BOOST_CHECK_EQUAL(gs.map.width, 15);
  for(int i =0; i<gs.map.height;++i) {
      for(int j =0; j<gs.map.width;++j)
        std::cout << gs.map.field_[i][j];
      std::cout << std::endl;
  }
}
BOOST_AUTO_TEST_SUITE_END()
