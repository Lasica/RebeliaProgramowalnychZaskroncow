/*
 * Written by Artur Dobrogowski.
 * Copyright 2014
 */

#ifndef CLIENTLIST_H
#define CLIENTLIST_H

#include "Resource.h"
#include "Observer.h"
#include <boost/serialization/base_object.hpp>

class ClientList : public Resource, public Observer {
  public:
    ClientList();
  private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) const {
    }
};

#endif // CLIENTLIST_H
