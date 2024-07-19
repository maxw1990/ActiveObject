# Active Object library

Library which implement the active object pattern.

You can use an active object in as Pool or as one object:

```cpp
#include <ActiveObject.h>

ActiveObjectPool& pool = ActiveObjectPool::GetInstance();
pool.sendMessage(msg1);
pool.sendMessage(msg1);
//
//
pool.WaitAndstopAll();
```

or

```cpp
#include <Pool/ActiveObjectPool.h>

ActiveObject acObj;
acObj.send(msg1);
acObj.WaitAndStop();
```

For running specific task you have to wrap your task in a Message class
defined in Message.h Here is an example:

```cpp
class HandleMessage : public Message {
public:
    HandleMessage():result(0) {}
    bool execute() override {
        for(int i = 0; i< 10;i++){
            std::cout<<i<<std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            result += i;
        }
        return true;
    }
    int getResult(){
        return result;
    }
private:
int result;
};
```

## cmake config

configure Project with dev config by choosing dev from the drop down menu.
Or manually by using the flags:


```cmake
-DCMAKE_BUILD_TYPE=Debug 
-DAO_ENABLE_CUSTOM_INSTALL=ON 
-DAO_ENABLE_DEBUG_MODE=ON 
-DAO_CUSTOM_INSTALL_PATH=CustomPath
```
