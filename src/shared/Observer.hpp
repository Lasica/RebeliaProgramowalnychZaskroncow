#ifndef OBSERVER_H
#define OBSERVER_H

#include "shared/Resource.hpp"
#include "shared/Packet.hpp"
class Observer {

  public:
    Observer(unsigned id): observerID(id) {}
    unsigned observerID;
    static unsigned observerNextID;
    virtual void update(Packet &) { std::cout << "Warning! This method (Observer.update()) shouldn't be called!\n"; };
    virtual ~Observer() {};
};
#endif // OBSERVER_H
