#ifndef CHATHISTORY_H
#define CHATHISTORY_H

#include "Observer.h"
#include "Resource.h"
#include "ChatEntry.h"

#include <vector>
#include "ChatHistoryRaw.h"

class ChatHistory : public Observer, public Resource, protected ChatHistoryRaw {
  public:
    ~ChatHistory();
    std::vector<ChatEntry> chatLog_;
};

#endif // CHATHISTORY_H
