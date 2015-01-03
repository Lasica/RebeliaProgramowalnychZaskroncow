#ifndef RESOURCEFACTORY_H
#define RESOURCEFACTORY_H

#include "Resource.h"
#include <string>
#include <map>
#include <sstream>

class ResourceFactory {
  public:
    typedef std::stringstream codingStream;
    typedef Resource *(*CreateResourceFunction)(codingStream &);

    void register_resource(std::string idTag, CreateResourceFunction fun);
    Resource *create(std::string idTag, codingStream &str);

// singleton
    ResourceFactory &operator=(const ResourceFactory &) = delete;
    ResourceFactory(const ResourceFactory &) = delete;

    static ResourceFactory &getInstance();
  private:
    ResourceFactory();

    typedef std::map<std::string, CreateResourceFunction> Callbacks;
    Callbacks callbacks_;
};

#endif // RESOURCEFACTORY_H
