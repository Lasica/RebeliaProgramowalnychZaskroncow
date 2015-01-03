#ifndef CHATENTRY_H
#define CHATENTRY_H

#include "Resource.h"
#include "ChatEntryRaw.h"

class ChatEntry : protected ChatEntryRaw {
  public:
    ChatEntry();
    ~ChatEntry();

};

#endif // CHATENTRY_H
