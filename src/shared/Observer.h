/*
 * Written by Artur Dobrogowski.
 * Copyright 2014
 */

#ifndef OBSERVER_H
#define OBSERVER_H

#include "shared/Resource.h"

class Observer {
  public:
    virtual void update(Resource*) {};
    virtual ~Observer() {};
};

#endif // OBSERVER_H
