//Link to Boost
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE "AdresRegister functions test"

#include "server/Address.hpp"
#include "server/AddressRegister.hpp"
#include <boost/test/unit_test.hpp>

using namespace boost::unit_test;



BOOST_AUTO_TEST_SUITE( rejestracja_i_stalosc )
BOOST_AUTO_TEST_CASE( rejestracja ) {
    Address a("ip:a", 557);
    Address b("10.0.0.0", 12341);
    Address c("ip:c", 0);
    AddressRegister reg;
    a.change_owner(32);
    b.change_owner(12);
    c.change_owner(9);
    const Address *ptr;
    BOOST_REQUIRE_NO_THROW(reg.register_address(a));
    BOOST_REQUIRE_NO_THROW(ptr = reg.register_address(b));
    BOOST_REQUIRE_NO_THROW(reg.register_address(c));
    BOOST_CHECK_EQUAL(b.ip      ,   ptr->ip);
    BOOST_CHECK_EQUAL(b.port    ,   ptr->port);
    BOOST_CHECK_EQUAL(b.owner   ,   ptr->owner);
}
BOOST_AUTO_TEST_CASE( ponowna_rejestracja ) {
    Address a("ip:a", 557);
    AddressRegister reg;
    const Address *ptr;
    BOOST_REQUIRE_NO_THROW(ptr = reg.register_address(a));
    BOOST_CHECK_EQUAL(ptr->owner, INVALID_CLIENT_ID);
    a.change_owner(43);
    const Address *ptr2;
    BOOST_REQUIRE_NO_THROW(ptr2 = reg.register_address(a));
    BOOST_CHECK_EQUAL(ptr, ptr2);
    BOOST_CHECK_EQUAL(ptr->owner, 43);
    a.ip = "ip:321";
    BOOST_REQUIRE_NO_THROW(ptr2 = reg.register_address(a));
    BOOST_CHECK(ptr != ptr2);
    BOOST_CHECK_EQUAL(ptr->ip, "ip:a");
    BOOST_CHECK_EQUAL(ptr2->ip, a.ip);
}
BOOST_AUTO_TEST_CASE( zmiana_ownera ) {
    Address a("ip:a", 557);
    AddressRegister reg;
    a.change_owner(231);
    const Address *ptr;
    BOOST_REQUIRE_NO_THROW(ptr = reg.register_address(a));
    BOOST_CHECK_EQUAL(231, reg.get_address_owner(a));
    BOOST_CHECK_EQUAL(231, reg.get_address_owner(Address("ip:a", 557)));
    ptr->change_owner(7);
    BOOST_CHECK_EQUAL(7, reg.get_address_owner(Address("ip:a", 557)));
}
BOOST_AUTO_TEST_CASE( pointer ) {
    Address a("ip:a", 557);
    AddressRegister reg;
    a.change_owner(231);
    const Address *ptr;
    BOOST_REQUIRE_NO_THROW(ptr = reg.register_address(a));
    BOOST_CHECK_EQUAL(ptr, reg.get_address_pointer(a));
    BOOST_CHECK_EQUAL(ptr, reg.get_address_pointer(Address("ip:a", 557)));
}
BOOST_AUTO_TEST_SUITE_END()
