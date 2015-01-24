#ifndef CHATHISTORY_H
#define CHATHISTORY_H

#include "Subject.hpp"
#include "ChatEntryRaw.hpp"

#include <vector>

class ChatRegister : public Subject {
public:
    void register_message(ChatEntryRaw &message);
private:
    std::vector<ChatEntryRaw> chatLog_;
    //void notify(const Resource*, const Packet::Tag);
};

#endif // CHATHISTORY_H
