#ifndef WORLD_HPP
#define WORLD_HPP
#include <iostream>
#include <cstdio>
#include <vector>
#include "luacore/luafuncs.hpp"

typedef char MapUnit;

class Map {
public:
    Map(): width(10), height(10), baseMapUnit_('.') {}
    void map_resize(int x, int y) {
        if(x > 20) x = 20;
        if(y > 20) y = 20;
        if(y > height) {
            for(int i=0; i< y-height; ++i) {
                field_.push_back(std::vector<MapUnit>());
            }
        } else {
            field_.resize(y);
        }
        for(int i=0; i < y; ++i) {
            field_[i].resize(x, baseMapUnit_);
        }
        width = x;
        height = y;
    }
    void set_base_map_unit(const MapUnit &a) { baseMapUnit_ = a; }
    void set_field(const int &x, const int &y, const MapUnit &character) {
        if(x >=0 && x < width && y >=0 && y < height) {
            field_[y][x] = character;
        }
    }
private:
    int width;
    int height;
    MapUnit baseMapUnit_;
    std::vector<std::vector<MapUnit>> field_; //map[y][x]
};
#endif
