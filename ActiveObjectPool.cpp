#include "ActiveObjectPool.h"


ActiveObjectPool& ActiveObjectPool::GetInstance(){
    static ActiveObjectPool threadPool;
    return threadPool;
 }

void ActiveObjectPool::sendMessage(std::shared_ptr<Message> msg) {
    std::lock_guard<std::mutex> lock(mutex);
    #ifndef __NDEBUG__
    printf("receive message\n");
    #endif
    messages.push(msg);
    condition.notify_one();
}

void ActiveObjectPool::WaitAndstopAll() {
    std::unique_lock<std::mutex> lock(mutex);
    #ifndef __NDEBUG__
    printf("Pool Waiting for ending...\n");
    #endif
    condition.wait(lock, [this]{ return messages.empty();});
    running = false;
    lock.unlock();
    #ifndef __NDEBUG__
    printf("Thread Pool executing stop\n");
    #endif
    condition.notify_one();
    if(thread.joinable()){
        thread.join();
    }
    for (auto obj : objects) {
        obj->WaitAndStop();
    }
}

ActiveObjectPool::ActiveObjectPool():thread(&ActiveObjectPool::run, this),running(true) {
    for (size_t i = 0; i < 8; ++i) {
        objects.push_back(std::make_shared<ActiveObject>());
        m_IdleObjectQueue.push(objects.back());
    }
}

void ActiveObjectPool::run() {
    while (running) {
        std::unique_lock<std::mutex> lock(mutex);
        condition.wait(lock, [this] { return !messages.empty() || !running; });
        if (!running) break;

        std::shared_ptr<Message> msg = messages.front();
        messages.pop();
        lock.unlock();
        // Nachricht verarbeiten
        if(!m_IdleObjectQueue.empty()){
            std::shared_ptr<ActiveObject> worker = m_IdleObjectQueue.front();
            m_IdleObjectQueue.pop();
            #ifndef __NDEBUG__
            printf("Send message to worker: %i \n", worker->getThreadID());
            #endif
            worker->send(msg);
        }
        else{
            while(m_IdleObjectQueue.empty()){
                for(auto obj : objects){
                    if(obj->isActive()){
                        #ifndef __NDEBUG__
                        printf("object ready %i \n",obj->getThreadID());
                        #endif
                        m_IdleObjectQueue.push(obj);
                    }
                }
            }
        }
        //check if all messages where processed
        if(messages.empty()){
            condition.notify_one();
        }
    }
}

ActiveObjectPool::~ActiveObjectPool(){
    if(thread.joinable()){
        thread.join();
    }
}