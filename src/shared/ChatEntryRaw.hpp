#ifndef CHATENTRYRAW_H
#define CHATENTRYRAW_H

#include <boost/serialization/base_object.hpp>
#include <boost/serialization/export.hpp>       //makro BOOST_CLASS_EXPORT

#include <string>
#include "shared/Resource.hpp"

struct ChatEntryRaw;
// nie ma pliku .cpp z implementacją metod, więc należy użyć tego makra, a nie BOOST_CLASS_EXPORT_KEY()
// (po prostu zadziałało, kiedy zmieniłem to makro)
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
