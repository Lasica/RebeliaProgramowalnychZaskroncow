#ifndef OBSERVER_H
#define OBSERVER_H

#include "shared/Resource.hpp"

class Observer {

  public:
    unsigned observerID = 0;
    virtual void update(Resource *) { };
    virtual ~Observer() {};
};

#endif // OBSERVER_H
