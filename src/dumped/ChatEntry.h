#ifndef CHATENTRY_H
#define CHATENTRY_H

#include "Resource.hpp"
#include "ChatEntryRaw.hpp"

class ChatEntry : protected ChatEntryRaw {
  public:
    ChatEntry();
    ~ChatEntry();

};

#endif // CHATENTRY_H
