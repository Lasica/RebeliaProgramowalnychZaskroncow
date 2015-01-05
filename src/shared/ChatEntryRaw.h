#ifndef CHATENTRYRAW_H
#define CHATENTRYRAW_H

#include <boost/serialization/base_object.hpp>
#include <string>
#include "shared/Resource.h"
#include "shared/Packet.hpp"

class ChatEntryRaw : public Resource {
  private:
    friend class boost::serialization::access;
    // When the class Archive corresponds to an output archive, the
    // & operator is defined similar to <<.  Likewise, when the class Archive
    // is a type of input archive the & operator is defined similar to >>.
    template<class Archive>
    void serialize(Archive &ar, const unsigned int) {
        ar &nick_;
        ar &message_;
    }
  public:
    const static  PacketTag idTag_;
    std::string nick_;
    std::string message_;
    ChatEntryRaw() {};
    ChatEntryRaw(const std::string &nick__, const std::string &message__) :
        nick_(nick__), message_(message__) {
    }
};


const PacketTag ChatEntryRaw::idTag_ = CHAT_ENTRY;

#endif //CHATENTRYRAW_H
