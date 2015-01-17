#ifndef PACKET_HANDLER_H
#define PACKET_HANDLER_H

#include <chrono>
#include <thread>
#include <queue>
#include "shared/Packet.hpp"
#include "shared/typedefinitions.hpp"

class Packet_handler {
  public:
    Packet_handler(std::queue<Packet> *inQueue, bool *running) :
        inQueue_(inQueue), running_(running) { }
    void operator()();
  private:
    PacketQueue *const inQueue_;
    bool *const running_;
};

#endif // PACKET_HANDLER_H
