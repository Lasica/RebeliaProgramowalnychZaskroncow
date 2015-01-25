#include "server/Packet_handler.hpp"
#include "shared/HandshakeRaw.hpp"
#include "shared/ChatEntryRaw.hpp"
#include "server/Server.hpp"

#include <iostream>
#include <assert.h>

void Packet_handler::operator()() {

    std::cout << "Packet handler has started\n";
    try {
        while(*running_) {
            while(!inQueue_->empty()) {
                Packet *top = &inQueue_->front();
                std::cout << "Handling packet with tag " << top->get_tag() << std::endl;

                switch(top->get_tag()) {
                case Packet::REGISTER_REQUEST: {            // Handshake
                    HandshakeRaw* hr(static_cast<HandshakeRaw*>((top->get_content()).get()));
                    TcpServer::getInstance().connectedClients.register_client(top->get_address(), top->get_address()->connection, hr->nick_);
                        } /*break;*/

                case Packet::SYNCHRONISE_REQUEST: {        // prosba o wyslanie wszystkich zasobow...
//                     ClientID s = TcpServer::getInstance().registeredAddresses.get_address_owner(*(top->get_address())); //pobiera id klienta o adresie zapisanym w pakiecie
//                     Observer* obs((TcpServer::getInstance().connectedClients.look_up_with_id(s).get())); //rzutowanie z ClientPtr na Observer*
//                     TcpServer::getInstance().connectedClients.synchronise(obs);   //kolejno wywoływane metody synchronise u każdego z obserwatorów
//                     TcpServer::getInstance().registeredChat.synchronise(obs);
//                     TcpServer::getInstance().registeredRooms.synchronise(obs);
                    } break;

                case Packet::CHAT_ENTRY_MESSAGE_REQUEST: {   // prosba o nadanie wiadomosci czatu
                    ChatEntryRaw* cer(static_cast<ChatEntryRaw*>((top->get_content()).get()));
                    TcpServer::getInstance().registeredChat.register_message(*cer);
                } break;

                case Packet::GAMEROOM_CREATE_REQUEST: {    // prosba o stworzenie nowego pokoju
                    GameRoomRaw* gr(static_cast<GameRoomRaw*>((top->get_content()).get()));
                    GameRoomPtr gpt =  TcpServer::getInstance().registeredRooms.add_game_room(gr->host, gr->gameRoomName);
                    // w metodzie add_gameroom() host jest automatycznie dodany do listy graczy
                } break;

                case Packet::GAMEROOM_JOIN_REQUEST: {      // prosba o dolaczenie do pokoju
                    GameRoomRaw* gr(static_cast<GameRoomRaw*>((top->get_content()).get()));
                    GameRoomPtr gpt =  TcpServer::getInstance().registeredRooms.look_up_with_id(gr->id);
                    gpt->add_player(TcpServer::getInstance().registeredAddresses.get_address_owner(*(top->get_address())));
                } break;

                case Packet::GAMEROOM_LEAVE_REQUEST: {     // prosba o opuszczenie pokoju
                    ClientID l = TcpServer::getInstance().registeredAddresses.get_address_owner(*(top->get_address()));
                    GameRoomID gr = TcpServer::getInstance().connectedClients.get_state(l).locationIdentifier;
                    GameRoomPtr gpt = TcpServer::getInstance().registeredRooms.look_up_with_id(gr);
                    gpt->remove_player(l);
                } break;

                case Packet::LOG_OUT_REQUEST: {
                    ClientID rm = TcpServer::getInstance().registeredAddresses.get_address_owner(*(top->get_address()));
                    TcpServer::getInstance().connectedClients.remove_client(rm);
                    // GameRoom, w którym był ten gracz, powinien być obserwatorem ClientsRegister, jeśli ma się dowiedzieć o jego wyjściu lub w ClientsRegister i metodzie remove_client powinno być zrobione zawiadomienie odpowiedniego gameroomu
                }
                //case Packet::GAMEROOM_UPDATE_REQUEST:    // prosba o zmiane ustawien pokoju
                //case Packet::GAMEROOM_START_REQUEST:     // prosba o rozpoczecie rozgrywki
                //case Packet::GAME_START_FAILURE_INFO:    // informacja dla klienta o niespelnionym rzadaniu
                //case Packet::CLOCK_SYNCHRONISE:          // prosba o okreslenie czasu wzgledem serwera
                //case Packet::GAME_STATE:                 // pakiet zawierajacy stan rozgrywki
                //case Packet::GAME_ACTION:                // byc moze sie przyda?
                case Packet::KEEP_ALIVE: {                 // ping! do ustalenia czy ktos stracil polaczenie.
                    std::cout << "Keeping alive client ";
                    ClientID x=TcpServer::getInstance().registeredAddresses.get_address_owner(*(top->get_address()));
                    std::cout << x << std::endl;
                } break;
                case Packet::UPDATED_RESOURCE: {           // dane aktualizacyjne przeznaczone dla klienta
//                     pokazuje na cout zawartość odebranego pakietu (tylko dla testów)
                    std::cout << top->get_tag() << " " << top->show_resource_content() << std::endl;
                } break;
                default:
                    std::cout << "Unexpected packet received. Tag: " << top->get_tag() << std::endl ;
                    std::cout << top->get_data_streambuf() << std::endl;
                    break;
                }

                inQueue_->pop();
            }

            std::this_thread::yield();
        }
    } catch(std::exception &e) {
        std::cout << "Exception at Packet_handler." << e.what() << "\n Packet Queue status:" <<
        inQueue_->size() << " " << std::endl;
    }

    std::cout << "Packet handler has finished\n";
}

