#ifndef CHATENTRY_H
#define CHATENTRY_H

#include "Resource.h"
#include "ChatEntryRaw.h"

class ChatEntry : public Resource, protected ChatEntryRaw {
  public:
    ChatEntry();
    ~ChatEntry();

  private:
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) const { }
};

#endif // CHATENTRY_H
