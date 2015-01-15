#ifndef PACKET_HANDLER_H
#define PACKET_HANDLER_H

#include <chrono>
#include <thread>
#include <queue>
#include "shared/Packet.hpp"
#include "shared/typedefinitions.h"

class Packet_handler {
  public:
    Packet_handler(std::queue<Packet> *inQueue, bool *running, std::chrono::milliseconds sleepTime) :
        inQueue_(inQueue), running_(running), sleepTime_(sleepTime) { }
    void operator()();
  private:
    PacketQueue *const inQueue_;
    bool *const running_;
    std::chrono::milliseconds sleepTime_;
};

#endif // PACKET_HANDLER_H
