#include "shared/ChatRegister.hpp"

void ChatRegister::notify() {
    for(Observer *o : obs_)
        o->update(&(chatLog_.back()));
}

void ChatRegister::register_message(ChatEntryRaw &message) {
    chatLog_.push_back(message);
    notify();
}
