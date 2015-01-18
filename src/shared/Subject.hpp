#ifndef SUBJECT_H
#define SUBJECT_H

#include "Observer.hpp"
#include <string>
#include <vector>


class Subject {
public:
    virtual ~Subject() {};
    void addObserver(Observer *o) {
        obs_.push_back(o);
    }
    virtual void notify() = 0;
protected:
    std::vector<Observer *> obs_;
};

#endif // SUBJECT_H
