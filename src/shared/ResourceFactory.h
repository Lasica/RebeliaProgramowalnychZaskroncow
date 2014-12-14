#ifndef RESOURCEFACTORY_H
#define RESOURCEFACTORY_H

#include "Resource.h"
#include <string>
#include <boost/archive/text_iarchive.hpp>
#include <map>

class ResourceFactory {
  public:
    typedef Resource *(*CreateResourceFunction)(boost::archive::text_iarchive &);
    void register_resource(std::string idTag, CreateResourceFunction fun);
    Resource *create(std::string idTag, boost::archive::text_iarchive &ia);
// singleton
    ResourceFactory &operator=(const ResourceFactory &) = delete;
    ResourceFactory(const ResourceFactory&) = delete;
    static ResourceFactory &getInstance();
  private:
    ResourceFactory();

    typedef std::map<std::string, CreateResourceFunction> Callbacks;
    Callbacks callbacks_;
};

#endif // RESOURCEFACTORY_H
