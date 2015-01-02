#include "ResourceFactory.h"

ResourceFactory::ResourceFactory() {
    /* TODO: rejestracja */
}

Resource *ResourceFactory::create(std::string idTag, boost::archive::text_iarchive &ia) {
    Callbacks::const_iterator i = callbacks_.find(idTag);

    if(i == callbacks_.end()) {
        throw "Unidentified type for factory creation"; //TODO blad - nieznany typ
    } else
        return (i->second)(ia);
}

void ResourceFactory::register_resource(std::string idTag, ResourceFactory::CreateResourceFunction fun) {
    if(callbacks_.find(idTag) != callbacks_.end())
        callbacks_[idTag] = fun;
    else
        throw "Unacceptable situation: trying to re-register object with the same id";   // TODO blad
}

ResourceFactory &ResourceFactory::getInstance() {
    static ResourceFactory fact;
    return fact;
}


