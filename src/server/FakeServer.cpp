#include "FakeServer.h"
#include <iostream>
#include <vector>

FakeServer::FakeServer(int x, std::string channel_, std::string INS[num_of_connections] ) : num_of_connections(x), channel(channel_){
    std::cout << "Podaj nazwy kanalow wejsciowych (" << num_of_connections <<")\n";
    for(int i=0; i<num_of_connections; ++i) {
        out_names[i] << '0'+i << '_' << channel;
        in_names[i] = INS[i];
    }
}

void FakeServer::run() // do odpalenia w innym watku?
{
    // dodac watki do odpalenia
    running=true;
    while(running) {
        // sprawdz iny
        for(int i=0; i<num_of_connections; ++i) {
            running = scan_file(i);
        }
        // sprawdz kolejke wysylkowa
        while(!to_send.empty()) {
            Packet a = to_send.front();
            to_send.pop();
            int address = a.get_address();
            std::streambuff data = a.get_data_streambuf();
            send(address, data);
        }
    }
}

bool FakeServer::scan_file(int x)
{
    try {
        std::string line;
        while(true) {
            outs[x].open(out_names[x]);
            if(outs[x].is_open()) break;
        }
        // wczytaj i handluj jako pakiet, jesli bylo exit - to exit.
        while ( getline (outs[x],line) )
        {
            std::cout << line << '\n';
            if(line == "exit")
                running = false;
        }
        outs[x].close();
    }
    catch(...) {
    }
    return false;
}

void FakeServer::send(int x, std::stringstream data)
{
    while(true) {
        ins[x].open(in_names[i]);
        if(ins[x].is_open()) break;
    }
    ins[x] << data;
    ins[x].close();
}
