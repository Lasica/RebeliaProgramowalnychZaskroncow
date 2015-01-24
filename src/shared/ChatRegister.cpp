#include "shared/ChatRegister.hpp"
#include <boost/shared_ptr.hpp>

void ChatRegister::register_message(ChatEntryRaw &message) {
    chatLog_.push_back(message);
    Packet::Tag tag = Packet::UPDATED_RESOURCE;
    boost::shared_ptr<Resource> notification(new ChatEntryRaw(message));
    notify(&*notification, tag);
}
