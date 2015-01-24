#define BOOST_TEST_DYN_LINK

#define BOOST_TEST_MODULE ClientTestModule

#include "server/ClientDataRaw.hpp"
#include "server/Client.hpp"
#include "server/Address.hpp"
#include <boost/test/unit_test.hpp>


// TODO:
// - kiedy struktura Address będzie miała już właściwą postać i właściwy typ
//  można zamienić domyślne konstruktory Address na parametryzowane
/* FIXME: Adres IP ma być string
BOOST_AUTO_TEST_SUITE( ConstructorsTests )

BOOST_AUTO_TEST_CASE( parametrized_ctor_1 ) {

    Address testAd = Address(5,6);
    Client test = Client("test", testAd, ClientState(ClientState::LOBBY, 0));

    BOOST_CHECK_EQUAL(test.get_nickname(), "test");
    BOOST_CHECK_EQUAL(test.get_address().port, testAd.port);
    BOOST_CHECK_EQUAL(test.get_address().ip, testAd.ip);
    BOOST_CHECK_EQUAL(test.state_.location, ClientState::LOBBY);
    BOOST_CHECK_EQUAL(test.state_.locationIdentifier, 0);
}


BOOST_AUTO_TEST_CASE( copy_ctor ) {

    Address copyTestAd = Address(3, 4);

    Client sample = Client("sample", copyTestAd, ClientState(ClientState::GAME, 3));
    Client copy(sample);
    BOOST_CHECK_EQUAL(copy.get_nickname(), sample.get_nickname());
    BOOST_CHECK_EQUAL(copy.get_address().port, sample.get_address().port);
    BOOST_CHECK_EQUAL(copy.get_address().ip, sample.get_address().ip);
    BOOST_CHECK_EQUAL(copy.state_.location, sample.state_.location);
    BOOST_CHECK_EQUAL(copy.state_.locationIdentifier, sample.state_.locationIdentifier);
}

BOOST_AUTO_TEST_SUITE_END()



BOOST_AUTO_TEST_SUITE( SetMethods )

    Address setTestAd = Address(15,36);


    Client setTests("setTest", setTestAd, ClientState(ClientState::GAMEROOM, 12));

BOOST_AUTO_TEST_CASE( state ) {

    setTests.set_state(ClientState(ClientState::LOBBY, 0));
    BOOST_CHECK_EQUAL(setTests.get_state().location, ClientState::LOBBY);
    BOOST_CHECK_EQUAL(setTests.get_state().locationIdentifier, 0);
}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE( OperatorLessThan )

    // Operator:
    // 1. compares ports
    // 2. compares ips

    Address greaterIpAd = Address(100,1);
    Address lesserIpAd = Address(1, 1);

    Address greaterPortAd = Address(1, 100);
    Address lesserPortAd = Address(1,1);

    Address twinAddressAd = Address(1,1);

    ClientState s(ClientState::LOBBY, 0);

    Client greaterIp("greaterIpClient", greaterIpAd, s);
    Client lesserIp("lesserIpClient",lesserIpAd, s);
    Client greaterPort("greaterPortClient", greaterPortAd, s);
    Client lesserPort("lesserPortClient", lesserPortAd, s);
    Client twinClient1("twinClient", twinAddressAd, s);
    Client twinClient2("twinClient", twinAddressAd, s);


BOOST_AUTO_TEST_CASE( different_ports ) {
    BOOST_CHECK(  lesserPort < greaterPort );
    BOOST_CHECK( !(greaterPort < lesserPort) );
}

BOOST_AUTO_TEST_CASE( different_ips) {
    BOOST_CHECK(  lesserIp < greaterIp  );
    BOOST_CHECK( !(greaterIp < lesserIp) );
}

BOOST_AUTO_TEST_CASE( equal ) {
    BOOST_CHECK( !(twinClient1 < twinClient2) );
}

BOOST_AUTO_TEST_SUITE_END()

*/



