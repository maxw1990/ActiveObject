#include <catch2/catch_test_macros.hpp>
#include "ActiveObject.h"
#include "Pool/ActiveObjectPool.h"
#include "IMessage.h"
#include <iostream>
#include <chrono>

class TestMessage: public Message{
    public:
    bool execute(){
        return true;
    };
};

class WaitMessage: public Message{
    public:
    bool execute(){
        std::cout << "WaitMessage running\n";
        std::this_thread::sleep_for(std::chrono::seconds(4));
        std::cout << "WaitMessage finished\n";
        return true;
    };
};

TEST_CASE("ActiveObject basic behavior") {
    ActiveObject obj;

    // Construct a message that just returns true
    auto msg = std::make_shared<TestMessage>();
    auto msg1 = std::make_shared<WaitMessage>();
    auto msg2 = std::make_shared<WaitMessage>();

    // Send message
    obj.send(msg);
    obj.send(msg1);
    obj.send(msg2);

    // Wait for all messages to be processed and stop
    obj.WaitAndStop();

    REQUIRE(obj.isActive() == false);
}

TEST_CASE("ActiveObjectPool basic behavior") {
    ActiveObjectPool& obj = ActiveObjectPool::GetInstance();

    // Construct a message that just returns true
    auto msg = std::make_shared<TestMessage>();
    auto msg1 = std::make_shared<WaitMessage>();
    auto msg2 = std::make_shared<WaitMessage>();

    // Send message
    obj.sendMessage(msg);
    obj.sendMessage(msg1);
    obj.sendMessage(msg2);

    // Wait for all messages to be processed and stop
    obj.WaitAndstopAll();

    REQUIRE(obj.isActive() == false);
}