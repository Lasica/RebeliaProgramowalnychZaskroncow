#define BOOST_TEST_DYN_LINK

#define BOOST_TEST_MODULE ClientsRegisterConcurrencyTestModule

#include <boost/test/unit_test.hpp>
#include "server/ClientsRegister.hpp"
#include "server/Address.hpp"
#include <boost/thread.hpp>

// Testy z wieloma wątkami są w oddzielnym pliku,
// aby odtworzyć warunki panujące w prawdziwym programie,
// gdzie jest tylko 1 instancja ClientsRegister.


BOOST_AUTO_TEST_SUITE( ClientsRegister_concurrency_tests )

// Wszystkie test case w tym suite operują na jednym obiekcie
ClientsRegister concurrencyTestCR;

const unsigned int iterations = 100000;
void registerThread() {
    Address ad;

    for(unsigned int i = 0; i < iterations; ++i)
        concurrencyTestCR.register_client(&ad, nullptr);
}

BOOST_AUTO_TEST_CASE( register_client_method ) {

    BOOST_REQUIRE_EQUAL(concurrencyTestCR.get_size(), 0);

    boost::thread_group registerThreads;
    registerThreads.create_thread(&registerThread);
    registerThreads.create_thread(&registerThread);
    registerThreads.join_all();

    BOOST_CHECK_EQUAL(concurrencyTestCR.get_size(), 2 * iterations);
}

unsigned int correctLookUps1 = 0, correctLookUps2 = 0;

void lookUpThread1() {
    ClientPtr pt;

    for(unsigned int i = 0; i < 2 * iterations; ++i) {
        pt = concurrencyTestCR.look_up_with_id(i);

        if(pt->get_client_id() == i)
            ++correctLookUps1;
    }
}

void lookUpThread2() {
    ClientPtr pt;

    for(unsigned int i = 0; i < 2 * iterations; ++i) {
        pt = concurrencyTestCR.look_up_with_id(i);

        if(pt->get_client_id() == i)
            ++correctLookUps2;
    }
}
BOOST_AUTO_TEST_CASE( look_up_with_id_method ) {

    //sprawdzenie, czy program nie zawiesi się
    BOOST_REQUIRE_EQUAL(concurrencyTestCR.get_size(), 2 * iterations);

    boost::thread_group lookUpThreads;
    lookUpThreads.create_thread(lookUpThread1);
    lookUpThreads.create_thread(lookUpThread2);
    lookUpThreads.join_all();

    BOOST_CHECK_EQUAL(correctLookUps1, 2 * iterations);
    BOOST_CHECK_EQUAL(correctLookUps2, 2 * iterations);

    correctLookUps1 = 0;
    correctLookUps2 = 0;
}


void changeStateThread1() {
    for(unsigned int i = 0; i < iterations; ++i)
        concurrencyTestCR.change_state(i, ClientState(ClientState::GAME, i));
}

void changeStateThread2() {
    for(unsigned int i = 0; i < iterations; ++i)
        concurrencyTestCR.change_state(i + iterations, ClientState(ClientState::GAMEROOM, i + iterations));
}

void changeStateThread3() {
    for(unsigned int i = 0; i < iterations; ++i)
        concurrencyTestCR.change_state(i, ClientState(ClientState::LOBBY, i + iterations));
}

BOOST_AUTO_TEST_CASE( change_state_method ) {
    BOOST_REQUIRE_EQUAL(concurrencyTestCR.get_size(), 2 * iterations);
    // Początkowo każdy Client ma state == LOBBY i location == 0
    boost::thread_group changeStateThreads;
    changeStateThreads.create_thread(changeStateThread1);
    changeStateThreads.create_thread(changeStateThread2);
    changeStateThreads.join_all();

    int lobbys = 0, gamerooms = 0, games = 0;

    for (unsigned int i = 0; i < 2 * iterations; ++i) {
        ClientState::Location l = concurrencyTestCR.look_up_with_id(i)->get_state().location;

        if(l == ClientState::GAME)
            games++;
        else if(l == ClientState::GAMEROOM)
            gamerooms++;
        else
            lobbys++;
    }

    BOOST_CHECK_EQUAL(lobbys, 0);
    BOOST_CHECK_EQUAL(games, iterations);
    BOOST_CHECK_EQUAL(gamerooms, iterations);

    // 2 wątki modyfikujące te same obiekty
    boost::thread_group changeStateThreads2;
    changeStateThreads2.create_thread(changeStateThread1);
    changeStateThreads2.create_thread(changeStateThread3);
    changeStateThreads2.join_all();

    lobbys = 0;
    gamerooms = 0;
    games = 0;

    for (unsigned int i = 0; i < iterations; ++i) {
        ClientState::Location l = concurrencyTestCR.look_up_with_id(i)->get_state().location;

        if(l == ClientState::GAME)
            games++;
        else if(l == ClientState::GAMEROOM)
            gamerooms++;
        else
            lobbys++;
    }

    BOOST_CHECK_EQUAL( gamerooms, 0 );
}

unsigned int correctGetStates1 = 0, correctGetStates2 = 0;

void getStateThread1() {
    for(unsigned int i = 0; i < 2 * iterations; ++i) {
        if(concurrencyTestCR.get_state(i).location == ClientState::GAMEROOM)
            ++correctGetStates1;
    }
}

void getStateThread2() {
    for(unsigned int i = 0; i < 2 * iterations; ++i) {
        if(concurrencyTestCR.get_state(i).location == ClientState::GAMEROOM)
            ++correctGetStates2;
    }
}

BOOST_AUTO_TEST_CASE( get_state_method ) {
    // najpierw ustawiam wszystkie ClientState::location na GAMEROOM
    for(unsigned int i = 0; i < 2 * iterations; ++i)
        concurrencyTestCR.change_state(i, ClientState(ClientState::GAMEROOM, i + iterations));


    //sprawdzenie, czy program nie zawiesi się

    BOOST_REQUIRE_EQUAL(concurrencyTestCR.get_size(), 2 * iterations);

    boost::thread_group getStateThreads;
    getStateThreads.create_thread(getStateThread1);
    getStateThreads.create_thread(getStateThread2);
    getStateThreads.join_all();

    BOOST_CHECK_EQUAL(correctGetStates1, 2 * iterations);
    BOOST_CHECK_EQUAL(correctGetStates2, 2 * iterations);

    correctGetStates1 = 0;
    correctGetStates2 = 0;

}

void removeThread1() {
    for(unsigned int i = 0; i < iterations; ++i)
        concurrencyTestCR.remove_client(i);
}

void removeThread2() {
    for(unsigned int i = 0; i < iterations; ++i)
        concurrencyTestCR.remove_client(i + iterations);
}

BOOST_AUTO_TEST_CASE( client_remove ) {
    BOOST_REQUIRE_EQUAL(concurrencyTestCR.get_size(), 2 * iterations);

    boost::thread_group removeThreads;
    removeThreads.create_thread(&removeThread1);
    removeThreads.create_thread(&removeThread2);
    removeThreads.join_all();
    BOOST_CHECK_EQUAL(concurrencyTestCR.get_size(), 0);

}

BOOST_AUTO_TEST_SUITE_END()
