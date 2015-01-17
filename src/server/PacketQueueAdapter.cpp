#include "server/PacketQueueAdapter.hpp"

void PacketQueueAdapter::push(const Packet& packet) {
    boost::mutex::scoped_lock scoped_lock(mtx_);
    queue_.push(packet);
}
void PacketQueueAdapter::pop() {
    boost::mutex::scoped_lock scoped_lock(mtx_);
    queue_.pop();
}
Packet& PacketQueueAdapter::front() {
    boost::mutex::scoped_lock scoped_lock(mtx_);
    return queue_.front();
}
bool PacketQueueAdapter::empty() {
    boost::mutex::scoped_lock scoped_lock(mtx_);
    return queue_.empty();
}
