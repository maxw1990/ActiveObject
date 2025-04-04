#pragma once
#include "IMessage.h"
#include "ActiveObject.h"

class ActiveObjectPool {
public:
    static ActiveObjectPool& GetInstance();
    ~ActiveObjectPool();

    void sendMessage(std::shared_ptr<Message> msg);

    void WaitAndstopAll();

private:
    void run();
    ActiveObjectPool();
    std::thread thread;
    std::vector<std::shared_ptr<ActiveObject>> objects;
    std::atomic_bool running;
    std::mutex mutex;
    std::condition_variable condition;
    std::queue<std::shared_ptr<Message>> messages;
    std::queue<std::shared_ptr<ActiveObject>> m_IdleObjectQueue;
};