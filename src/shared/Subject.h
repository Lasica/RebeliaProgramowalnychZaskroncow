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
    void addObserver(Observer *o) {
        obs_.push_back(o);
    }
    virtual void notify() = 0;
//     {
//         for(Observer *o : obs_)
//             o->update();
//     }
  protected:
    std::vector<Observer *> obs_;
};

#endif // SUBJECT_H
