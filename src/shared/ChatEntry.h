#ifndef CHATENTRY_H
#define CHATENTRY_H

#include "Resource.h"
#include "ChatEntryRaw.h"

class ChatEntry : public Resource, protected ChatEntryRaw {
  public:
    ChatEntry();
    ~ChatEntry();

};

#endif // CHATENTRY_H
