#include "shared/ChatRegister.hpp"
#include <boost/shared_ptr.hpp>

void ChatRegister::register_message(ChatEntryRaw &message) {
    chatLog_.push_back(message);
    Packet::Tag tag = Packet::UPDATED_RESOURCE;
    boost::shared_ptr<Resource> notification(new ChatEntryRaw(message));
    notify(&*notification, tag);
}

// przesyła całą historię czatu
void ChatRegister::synchronise(Observer* obs) {
    for(auto r: chatLog_) {
        boost::scoped_ptr<Resource> notification( new ChatEntryRaw(r));
        Packet::Tag tag(Packet::UPDATED_RESOURCE);
        // woła update() tylko dla tego pojedynczego klienta
        obs->update(notification.get(), tag);
    }
}
