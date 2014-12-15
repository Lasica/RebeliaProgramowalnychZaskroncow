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
  private:
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) const { }
    std::vector<ChatEntry> chatLog_;
};

#endif // CHATHISTORY_H
