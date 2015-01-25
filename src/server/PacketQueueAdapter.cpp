#include "server/PacketQueueAdapter.hpp"
#include <assert.h>
void PacketQueueAdapter::push(const Packet& packet) {

    //assert(false);
    boost::mutex::scoped_lock scoped_lock(mtx_);

    queue_.push(packet);
}
void PacketQueueAdapter::pop() {
    boost::mutex::scoped_lock scoped_lock(mtx_);
    queue_.pop();
}

int PacketQueueAdapter::size() {
    boost::mutex::scoped_lock scoped_lock(mtx_);
    return queue_.size();
}


Packet& PacketQueueAdapter::front() {
    boost::mutex::scoped_lock scoped_lock(mtx_);
    return queue_.front();
}
bool PacketQueueAdapter::empty() {
    boost::mutex::scoped_lock scoped_lock(mtx_);
    return queue_.empty();
}

