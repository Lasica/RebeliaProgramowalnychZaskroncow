#ifndef CHATENTRY_H
#define CHATENTRY_H

#include "Resource.h"
#include <boost/serialization/base_object.hpp>

class ChatEntry : public Resource {
  public:
    ChatEntry();
    ~ChatEntry();

  private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) const { }
};

#endif // CHATENTRY_H
