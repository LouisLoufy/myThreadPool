#include <iostream>
#include <thread>
#include <semaphore>

// LeastMaxValue
std::counting_semaphore<2> csem(0); // 在 release 时可以增加不止1
std::binary_semaphore bsem(0);

/*
 * semaphore release <==> condition_variable notify
 * semaphore acquire <==> condition_variable wait
 */

void task() {
    std::cout << "ready to recv: acquire" << std::endl;
    csem.acquire();
    std::cout << "signal acquireed" << std::endl;
}

int main() {
    std::thread t0(task);
    std::thread t1(task);
    std::thread t2(task);

    std::cout << "ready to signal: release" << std::endl;
    csem.release(2);
    std::cout << "signal releaseed" << std::endl;

    t0.join();
    t1.join();
    t2.join();
}