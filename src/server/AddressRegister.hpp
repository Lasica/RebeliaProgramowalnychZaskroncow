#ifndef ADDRESSREGISTER_H
#define ADDRESSREGISTER_H

#include "server/Address.hpp"
#include <set>
#include <boost/thread/shared_mutex.hpp>

/*!
 * Rejestr adresów, z których nawiązano połączenie z serwerem.
 */

class AddressRegister
{
public:
    const Address*  register_address(const Address &x);             //! rejestracja adresu, z którego połączono się z serwerem
    ClientID        get_address_owner(const Address &x) const;      //! ta metoda "tłumaczy" id klienta na jego adres
    const Address*  get_address_pointer(const Address &x) const;
    AddressRegister() { }
private:
    AddressRegister(AddressRegister &a) = delete;
    std::set<Address> addresses_;
    mutable boost::shared_mutex access_;
};

#endif // ADDRESSREGISTER_H
