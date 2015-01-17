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
    void notify();
};

#endif // CHATHISTORY_H
