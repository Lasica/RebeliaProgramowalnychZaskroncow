#ifndef CHATHISTORY_H
#define CHATHISTORY_H

#include "Subject.h"
#include "ChatEntryRaw.h"

#include <vector>

class ChatRegister : public Subject {
  public:
    void register_message(ChatEntryRaw &message);
  private:
    std::vector<ChatEntryRaw> chatLog_;
    void notify();
};

#endif // CHATHISTORY_H
