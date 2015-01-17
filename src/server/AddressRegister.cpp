#include "AddressRegister.hpp"

const Address* AddressRegister::register_address(const Address& x) {
    auto it = addresses_.insert(x);
    if(it.second == false) {// already existing in set
        it.first->update_connection(x.connection);
        it.first->change_owner(x.owner);
    }
    return &(*it.first);
}

ClientID AddressRegister::get_address_owner(const Address& x) const {
    std::set<Address>::const_iterator it = addresses_.find(x);
    return (it != addresses_.end())? it->owner : INVALID_CLIENT_ID;
}

const Address* AddressRegister::get_address_pointer(const Address& x) const {
    std::set<Address>::const_iterator it = addresses_.find(x);
    return &(*it);
}

