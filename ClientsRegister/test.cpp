/* Kod testujący kolejne funkcjonalności klasy ClientsRegister */

#include <iostream>
#include "Client.hpp"
#include "ClientsRegister.hpp"


int main(){
    ClientsRegister::instance();
    ClientsRegister::instance().register_client("test", 20, "1.1.1.1", IN_LOBBY, "");
    ClientsRegister::instance().register_client("test2", 20, "2.2.2.2", IN_LOBBY, "");
    ClientsRegister::instance().register_client("test3", 20, "123.123.123.123", IN_LOBBY, "");
    ClientsRegister::instance().register_client("test4", 20, "123.123.123.123", IN_GAME, "g1");
    ClientsRegister::instance().register_client("test5", 20, "123.123.123.123", IN_GAME, "g2");





}
