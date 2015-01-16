#include "server/Packet_handler.h"
#include <iostream>


void Packet_handler::operator()() {
    std::cout << "Packet handler has started\n"; //TODO remove debug

    try {
        while(*running_) {
            while(!inQueue_->empty()) {
                Packet *top = &inQueue_->front();

                switch(top->get_tag()) {
                case Packet::RESOURCE: {
                    // pokazuje na cout zawartość odebranego pakietu (tylko dla testów)
                    std::cout << top->get_tag() << " " << top->show_resource_content() << std::endl;

                    switch(top->get_content()->get_tag()) {
                    case Resource::CHAT_ENTRY:
                        break;

                    default :
                        std::cout << "unknown resource \n";
                        break;
                    }

                    break;
                }

                default:
                    break; // unexpacted response, maybe inform client about error?
                }

                inQueue_->pop();
            }

            //std::this_thread::sleep_for(sleepTime_);
            std::this_thread::yield();
        }
    } catch(...) {
    }

    std::cout << "Packet handler has finished\n";
}

