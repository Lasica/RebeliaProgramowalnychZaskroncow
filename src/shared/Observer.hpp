#ifndef OBSERVER_H
#define OBSERVER_H

#include "shared/Resource.hpp"
#include "shared/Packet.hpp"
class Observer {

  public:
    Observer(unsigned id): observerID(id) {}
    unsigned observerID;
    static unsigned observerNextID;
    virtual void update(const Resource *, const Packet::Tag) { };
    virtual ~Observer() {};
};
#endif // OBSERVER_H
