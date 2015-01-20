#ifndef PACKET_HANDLER_H
#define PACKET_HANDLER_H

#include <chrono>
#include <thread>
#include "server/PacketQueueAdapter.hpp"
#include "shared/Packet.hpp"
#include "shared/typedefinitions.hpp"

/*!
 *  Ta klasa jest odpowiedzialna za przekazywanie wszystkich przychodzących pakietów w odpowiednie miejsca.
 *  Dzięki temu, że każdy pakiet jest oznaczony przez Tag mówiący, jakiego typu jest przychodząca informacja, można ją przesłać w odpowiednie miejsce.
 *  Przykład: informacja przenoszona przez pakiet o tagu REGISTER_REQUEST zostanie wykorzystana do dodania nowego gracza do rejestru klientów.
 *
 *  Packet_handler działa w oddzielnym wątku.
 */


class Packet_handler {
public:
    Packet_handler(PacketQueue *inQueue, bool *running) :
        inQueue_(inQueue), running_(running) { }
    void operator()();              //! serce Packet_handlera - metoda przekazująca przychodzące informacje do odpowiednich miejsc
private:
    PacketQueue *const inQueue_;    //! na tę kolejkę trafiają pakiety przychodzące z zewnątrz
    bool *const running_;
};

#endif // PACKET_HANDLER_H
