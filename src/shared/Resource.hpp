#ifndef RESOURCE_H
#define RESOURCE_H
#include <boost/serialization/base_object.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <string>

struct Resource {
    enum Tag {
        CHAT_ENTRY,
        CLIENT_DATA,
        GAMEROOM,
        HANDSHAKE
    };

    virtual ~Resource() {}
    virtual Tag get_tag() = 0;

    friend class boost::serialization::access;
    template<typename Archive>
    void serialize(Archive &/*ar*/, const unsigned int /*version*/) { }


    // tylko dla testów serializacji (dla porównywania oryginału i odtworzonego obiektu)
    virtual std::string show_content() = 0; // dobry pomysl!

};

#endif // RESOURCE_H
