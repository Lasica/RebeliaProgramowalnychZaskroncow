#ifndef CHATHISTORY_H
#define CHATHISTORY_H

#include "Observer.h"
#include "Resource.h"
#include "ChatEntry.h"

#include <vector>
#include <boost/serialization/base_object.hpp>


class ChatHistory : public Observer, public Resource {
  public:
    ~ChatHistory();
  private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) const { }
    std::vector<ChatEntry> chatLog_;
};

#endif // CHATHISTORY_H
