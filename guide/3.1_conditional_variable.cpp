#include <iostream>
#include <thread>
#include <mutex>
#include <deque>
#include <condition_variable>

std::mutex mtx;
std::deque<int> q;
std::condition_variable condv;

// producer
void producer() {
    int i = 0;
    while (true) {
        std::unique_lock<std::mutex> lock(mtx);
        q.push_back(i);
        /* 每向队列中存储一个数据，唤醒正在休眠或等待状态的线程函数 */
        condv.notify_one(); // 唤醒一个正在等待的线程
        // condv.notify_all(); // 唤醒正在等待的所有线程
        if (i < 999999) {
            ++i;
        } else {
            i = 0;
        }
    }
} 

// consumer
void consumer1() {
    int data = 0;
    while (true) {
        std::unique_lock<std::mutex> lock(mtx);
        /* 当队列为空时，让线程进入等待状态 */
        while (q.empty()) {
            condv.wait(lock);
        }
        data = q.front();
        q.pop_front();
        std::cout << "Get value from deque: " << data << std::endl;
    }
}

void consumer2() {
    int data = 0;
    while (true) {
        std::unique_lock<std::mutex> lock(mtx);
        /* 当队列为空时，让线程进入等待状态 */
        while (q.empty()) {
            condv.wait(lock);
        }
        data = q.front();
        q.pop_front();
        std::cout << "Get value from deque: " << data << std::endl;
    }
}

int main() {
    std::thread prod(producer);
    std::thread cons1(consumer1);
    std::thread cons2(consumer2);
    prod.join();
    cons1.join();
    cons2.join();
    return 0;
}