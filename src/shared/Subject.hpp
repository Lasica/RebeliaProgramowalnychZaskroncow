#ifndef SUBJECT_H
#define SUBJECT_H

#include "Observer.hpp"
#include <string>
#include <vector>
#include "server/Client.hpp"

class Subject {
public:
    virtual ~Subject() {};
    void addObserver(Observer *o) const {
        obs_.push_back(o);
    }
    void eraseObserver(Observer *o) {
	    std::vector<Observer*>::iterator it = obs_.begin();
	   for(; it < obs_.end(); ++it)
		  if((*it)->observerID == o->observerID)
		  {

                	obs_.erase(it);
	          break; 
		  }
    }
   virtual void notify(const Resource* r,const Packet::Tag t) {
    for(Observer *o : obs_)
        o->update(r, t);
   }
protected:
   mutable std::vector<Observer *> obs_;
};

#endif // SUBJECT_H
