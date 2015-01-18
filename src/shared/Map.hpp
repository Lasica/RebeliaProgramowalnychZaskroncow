#ifndef WORLD_HPP
#define WORLD_HPP
#include <iostream>
#include <cstdio>
#include <vector>

typedef char MapUnit;

class Map {
public:
    Map(): width(10), height(10), baseMapUnit_('.') { map_resize(width,height);}
    void map_resize(int x, int y) {
        if(x > 20) x = 20;
        if(y > 20) y = 20;
        if(x < 1) x = 1;
        if(y < 1) y = 1;
        field_.resize(y);
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
//private:
    std::vector<std::vector<MapUnit>> field_; //map[y][x]
    int width;
    int height;
    MapUnit baseMapUnit_;
};
#endif
