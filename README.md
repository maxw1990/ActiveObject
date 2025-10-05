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

or use a future class

```cpp
template<typename T>
class FutureMessage : public Message {
public:
    FutureMessage(std::function<T()> task)
        : task(std::move(task)), promise(std::make_shared<std::promise<T>>()) {}

    bool execute() override {
        try {
            T result = task();
            promise->set_value(result);
        } catch (...) {
            promise->set_exception(std::current_exception());
        }
        return true;
    }

    std::future<T> getFuture() {
        return promise->get_future();
    }

    bool hasPromise() const override { return true; }

private:
    std::function<T()> task;
    std::shared_ptr<std::promise<T>> promise;
};
```

and use it like this:

```cpp
ActiveObject ao;

auto message = std::make_shared<FutureMessage<int>>(
    []() -> int {
        // Task logic here
        std::this_thread::sleep_for(std::chrono::seconds(1));
        return 42; // Example result
    });

std::future<int> result = message->getFuture();
ao.send(message);

// Later...
int value = result.get(); // Blocks until the result is available
std::cout << "Result: " << value << std::endl;
```

## cmake config

configure Project with dev config by choosing dev from the drop down menu.
Or manually by using the flags:

```shell
-DCMAKE_BUILD_TYPE=Debug 
-DAO_ENABLE_CUSTOM_INSTALL=ON 
-DAO_ENABLE_DEBUG_MODE=ON 
-DAO_CUSTOM_INSTALL_PATH=CustomPath
```

or by the defined makefile:

```bash
make PRESET=debug
```

## Use in other projects

### With find_package

- first go into downloaded git repo.
- then build: make build
- then: make install

This will install the project on user/local (Mac)
If you want to install it in a local folder you have to set the flags:

```shell
-DAO_ENABLE_CUSTOM_INSTALL=ON
-DAO_CUSTOM_INSTALL_PATH=<Path/To/Lib>
```

Now you can include the project via:

```Cmake
set(CMAKE_PREFIX_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib/ActiveObject ${CMAKE_PREFIX_PATH})

find_package(ActiveObject 0.0.1 REQUIRED)

# Link the MyLib library
target_link_libraries(MyApp PRIVATE ActiveObject::ActiveObject)
```

#### Include dirs

```c++
#include<Pool/ActiveObjectPool.h>
#include<ActiveObject.h>
```

### FetchContent

```Cmake
# Include FetchContent module
include(FetchContent)

# Fetch the library
FetchContent_Declare(
    ActiveObject
    GIT_REPOSITORY https://github.com/maxw1990/ActiveObject.git
    GIT_TAG        main
)
FetchContent_MakeAvailable(ActiveObject)

target_link_libraries(MyApp PRIVATE ActiveObject::ActiveObject)
```

```c++
#include<Pool/ActiveObjectPool.h>
#include<ActiveObject.h>
```
