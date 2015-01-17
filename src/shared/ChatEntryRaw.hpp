#ifndef CHATENTRYRAW_H
#define CHATENTRYRAW_H

#include <boost/serialization/base_object.hpp>
#include <boost/serialization/export.hpp>       //makro BOOST_CLASS_EXPORT

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <string>
#include "shared/Resource.hpp"

struct ChatEntryRaw;
BOOST_CLASS_EXPORT_KEY(ChatEntryRaw)

struct ChatEntryRaw : public Resource {
    ChatEntryRaw() { }
    ChatEntryRaw(const std::string &nick__, const std::string &message__) :
        nick_(nick__), message_(message__) { }
    virtual ~ChatEntryRaw() { }

    virtual Resource::Tag get_tag() {
        return Resource::CHAT_ENTRY;
    }

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int) {
        //serializacja klasy bazowej
        ar &boost::serialization::base_object<Resource>(*this);
        //serializacja pól tej klasy
        ar &nick_;
        ar &message_;
    }

    std::string nick_;
    std::string message_;


    virtual std::string show_content() {
        return "** ChatEntry **, nick==" + nick_ + ", message==" + message_ + "\n";
    }

};

#endif //CHATENTRYRAW_H
