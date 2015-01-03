#include "ResourceFactory.h"
#include "shared/ChatEntryRaw.h"
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

Resource* buildChatEntryRaw(ResourceFactory::codingStream &str) {
    ChatEntryRaw* build = new ChatEntryRaw;
    boost::archive::text_iarchive ar(str);
    ar >> *build;
    return build;
}

ResourceFactory::ResourceFactory() {
    /* TODO: rejestracja */
    callbacks_.insert(std::pair<std::string, CreateResourceFunction>(ChatEntryRaw::idTag_, buildChatEntryRaw));
}

Resource *ResourceFactory::create(std::string idTag, codingStream &str) {
    Callbacks::const_iterator i = callbacks_.find(idTag);

    if(i == callbacks_.end()) {
        throw "Unidentified type for factory creation"; //TODO blad - nieznany typ
    } else
        return (i->second)(str);
}

void ResourceFactory::register_resource(std::string idTag, ResourceFactory::CreateResourceFunction fun) {
    if(callbacks_.find(idTag) != callbacks_.end())
        callbacks_[idTag] = fun;
    else
        throw "Unacceptable situation: trying to re-register object with the same id";    // TODO blad
}

ResourceFactory &ResourceFactory::getInstance() {
    static ResourceFactory fact;
    return fact;
}


