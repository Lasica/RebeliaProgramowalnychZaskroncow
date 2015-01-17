#include "server/Packet_handler.hpp"
#include <iostream>

void Packet_handler::operator()() {
    std::cout << "Packet handler has started\n"; //TODO remove debug
    try {
        while(*running_) {
            while(!inQueue_->empty()) {
                Packet *top = &inQueue_->front();

                switch(top->get_tag()) {
                    case Packet::REGISTER_REQUEST:             // Handshake
                        break;
                    case Packet::CHAT_ENTRY_MESSAGE_REQUEST:   // prosba o nadanie wiadomosci czatu
                        break;
                    //case Packet::GAMEROOM_CREATE_REQUEST:    // prosba o stworzenie nowego pokoju
                    //case Packet::GAMEROOM_JOIN_REQUEST:      // prosba o dolaczenie do pokoju
                    //case Packet::GAMEROOM_LEAVE_REQUEST:     // prosba o opuszczenie pokoju
                    //case Packet::GAMEROOM_UPDATE_REQUEST:    // prosba o zmiane ustawien pokoju
                    //case Packet::GAMEROOM_START_REQUEST:     // prosba o rozpoczecie rozgrywki
                    //case Packet::GAME_START_FAILURE_INFO:    // informacja dla klienta o niespelnionym rzadaniu
                    //case Packet::SYNCHRONISE_REQUEST:        // prosba o wyslanie wszystkich zasobow...
                    //case Packet::CLOCK_SYNCHRONISE:          // prosba o okreslenie czasu wzgledem serwera
                    //case Packet::GAME_STATE:                 // pakiet zawierajacy stan rozgrywki
                    //case Packet::GAME_ACTION:                // byc moze sie przyda?
                    //case Packet::KEEP_ALIVE:                 // ping! do ustalenia czy ktos stracil polaczenie.
                    case Packet::UPDATED_RESOURCE:             // dane aktualizacyjne przeznaczone dla klienta
                        // pokazuje na cout zawartość odebranego pakietu (tylko dla testów)
                        std::cout << top->get_tag() << " " << top->show_resource_content() << std::endl;
                    default:
                        std::cout << "Unexpected packet received.\n";
                        break;
                }

                inQueue_->pop();
            }

            std::this_thread::yield();
        }
    } catch(std::exception &e) {
        std::cout << "Exception at Packet_handler." << e.what() << std::endl;
    }
    std::cout << "Packet handler has finished\n";
}

