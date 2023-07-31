#include <iostream>
#include <thread>
#include <mutex>
#include <atomic>

std::atomic<int> globalVariable{0};
// std::atomic<int> globalVariable = 0; // 原子变量不能使用拷贝构造。

void task() {
    for (int i = 0; i < 1000; ++i) {
        {
            globalVariable++;
            globalVariable--;
        }
    }
}

int main() {
    std::thread t(task);
    t.join();

    std::cout << "current value is: " << globalVariable << std::endl;
}
