#ifndef CHATENTRYRAW_H
#define CHATENTRYRAW_H

#include <boost/serialization/base_object.hpp>

struct ChatEntryRaw {
    friend class boost::serialization::access;
  private:
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) const { }

};

#endif //CHATENTRYRAW_H
