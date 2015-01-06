/*
 * Written by Artur Dobrogowski.
 * Copyright 2014
 */

#ifndef RESOURCE_H
#define RESOURCE_H

#include <string>
#include "shared/Packet.hpp"

/*Byl zamiar utworzenia klasy ktora mozna tlumaczyc na archiwum
 * i z funkcja wirtualna serialise(), zeby wszystkie zasoby po niej dziedziczyly,
 * ale niestety mechanizm boost::serialise na to nie pozwala.
 */
class Resource {
  public:
    virtual ~Resource() = 0;
//   protected:
//   const static PacketTag idTag_;
};

#endif // RESOURCE_H
