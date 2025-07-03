#pragma once
#include "IMessage.h"
#include <stdlib.h>
#include <memory>
#include <mutex>
#include <thread>
#include <queue>

// Active object
class ActiveObject {
public:
    ActiveObject();
    ~ActiveObject();
    // send message
    void send(std::shared_ptr<Message> msg);

    // stop active object and wait
    void WaitAndStop();
    
    bool isActive() const;

    int getThreadID() const;
private:
    void run();
    std::thread thread;
    std::queue<std::shared_ptr<Message>> messages;
    std::mutex mutex;
    std::condition_variable condition;
    std::atomic_bool running;
    std::atomic<bool> active;
    const int threadID;
};