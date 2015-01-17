#include "Server.hpp"

namespace server {

TcpConnection::pointer TcpServer::ConIter::operator*() {
    return connections_[counter_];
}
TcpConnection::pointer TcpServer::ConIter::operator[](int i) {
    counter_ = i;
    return connections_[counter_];

}
TcpServer::ConIter &TcpServer::ConIter::operator++() {
    --counter_;
    return *this;
}
TcpServer::ConIter TcpServer::ConIter::operator+(int i) {
    TcpServer::ConIter tmp(*this);
    tmp.counter_ += i;
    return tmp;
}
TcpServer::ConIter TcpServer::ConIter::operator-(int i) {
    TcpServer::ConIter tmp(*this);
    tmp.counter_ -= i;
    return tmp;

}
TcpServer::ConIter &TcpServer::ConIter::operator=(const TcpServer::ConIter &it) {
    counter_ = it.counter_;
    mtx_ = it.mtx_;
    return *this;
}

TcpServer::ConIter &TcpServer::ConIter::operator--() {
    --counter_;
    return *this;
}
bool TcpServer::ConIter::operator==(TcpServer::ConIter &it) {
    if(connections_[counter_] == *it)
        return true;
    else
        return false;
}
bool TcpServer::ConIter::operator!=( TcpServer::ConIter &it) {
    if(connections_[counter_] != *it)
        return true;
    else
        return false;
}
void TcpServer::ConIter::close() {
    std::deque<TcpConnection::pointer>::iterator it = connections_.begin();
    it += counter_;
    mtx_->lock();
    connections_.erase(it);
    mtx_->unlock();
}

TcpServer::ConIter &TcpServer::ConIter::begin() {
    counter_ = 0;
    return *this;
}
TcpServer::ConIter &TcpServer::ConIter::end() {
    counter_ = connections_.size() - 2;
    return *this;
}




}
