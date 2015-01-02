/*
 * Written by Artur Dobrogowski.
 * Copyright 2014
 */

#ifndef SUBJECT_H
#define SUBJECT_H

#include "Observer.h"
#include <string>
#include <vector>


class Subject {
  public:
    virtual ~Subject() {};
    //virtual std::string getState() = 0; // jeszcze nie wiem czy potrzebne
    //virtual std::string getChange() = 0; // ale jesli powyzsza potrzebna to i ta
    void add_observer(Observer *o) {
        obs_.push_back(o);
    }
    void notify() {
        for(Observer *o : obs_)
            o->update();
    }
  private:
    std::vector<Observer *> obs_;
};

#endif // SUBJECT_H
