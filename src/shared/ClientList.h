/*
 * Written by Artur Dobrogowski.
 * Copyright 2014
 */

#ifndef CLIENTLIST_H
#define CLIENTLIST_H

#include "Resource.h"
#include "Observer.h"
#include "ClientListRaw.h"

class ClientList : public Resource, public Observer, protected ClientListRaw {
  public:
    ClientList();
  private:
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) const {
    }
};

#endif // CLIENTLIST_H
