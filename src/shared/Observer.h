/*
 * Written by Artur Dobrogowski.
 * Copyright 2014
 */

#ifndef OBSERVER_H
#define OBSERVER_H

class Observer {
  public:
    virtual void update() {};
    virtual ~Observer() {};
};

#endif // OBSERVER_H
