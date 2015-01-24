#ifndef ADDRESS_HPP
#define ADDRESS_HPP

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include "typedefinitions.hpp"

#include <string>
#include <iostream>

/*
 * Proponuje poważną zmianę, żeby zrobić klase typu ksiazka adresowa(AddressRegister), ktora bedzie mapą Adresow
 * z kluczem rozpoznawalnym dla serwera (czy to para ip,port, czy to wskaznik na tcpconnection), zeby wszyscy mogli w
 * krótkim czasie przetłumaczyć adres na ID. Przy czym jeśli połączenie na danym ip/porcie zostanie zerwane, to jedynie
 * id klienta i wskaznik na tcp connection sa ustawiane na 0, a adres jest pamietany.
 * Alternatywą dla mapy jest set z operatorem porownania z adresu, a wyszukiwanie z tego seta byloby metodami
 * lower/upper_bound(Adres(o_zadanym_ip)).
 * Do klasy Adres wyemigruje wskaznik na TCPConnection z Klienta, jak i kopia id Clienta ktory obecnie go posiada.
 * Wowczas klient tak jak i Packet posiadaliby jedynie (stały) wskaznik (najlepiej nie iterator, wskaznik! iterator umozliwialby dostep do "sasiednich" adresow) na swoj adres.
 * Natomiast w rejestrze klientow byloby sortowanie klientow po id.
 */

/*!
 * Obiekty tej klasy reprezenują w serwerze adresy, z których łączą się klienci.
 */

struct Address {
    Address(AddressIP Ip="non-defined", AddressPort Port=~0) : ip(Ip), port(Port), owner(INVALID_CLIENT_ID), connection(nullptr)  { }
    void change_owner(ClientID newOwner) const {
        owner = newOwner;
    }
    void update_connection(const TcpPointer& x) const {
        connection = x;
    }
    AddressIP                       ip;
    AddressPort                     port;
    mutable ClientID                owner;      //! przechowuje identyfikator klienta, który łączy się z tego adresu; pole jest inicjowane dopiero po dodaniu klienta do rejestru klientów
    mutable TcpPointer              connection; // const?
    bool operator<(const Address &latter) const;
};

std::ostream &operator<<(std::ostream &o, const Address &a);

#endif // ADDRESS_HPP
