#include "shared/Packet.hpp"
#include <queue>
#include <boost/thread/mutex.hpp>

class PacketQueueAdapter
{
public:
    void push(const Packet&);
    void pop();
    Packet& front();

    bool empty();

private:
    std::queue<Packet> queue_;
    boost::mutex       mtx_;
};


