#ifndef CHATHISTORYRAW_H
#define CHATHISTORYRAW_H

#include <boost/serialization/base_object.hpp>

struct ChatHistoryRaw {
    friend class boost::serialization::access;
private:
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) { }

};

#endif //CHATHISTORYRAW_H
