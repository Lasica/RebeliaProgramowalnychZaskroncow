#include "shared/ChatRegister.hpp"

void ChatRegister::notify(Resource* resource, const Packet::Tag* tag) {
    for(Observer *o : obs_)
        o->update(resource, tag);
}

void ChatRegister::register_message(ChatEntryRaw &message) {
    chatLog_.push_back(message);
    Packet::Tag tag = Packet::UPDATED_RESOURCE;
  notify(&(chatLog_.back()), &tag);
}
