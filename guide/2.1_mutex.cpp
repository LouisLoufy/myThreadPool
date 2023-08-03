#include <iostream>
#include <mutex>
#include <thread>

std::mutex mtx1;
std::mutex mtx2;

int globalVariable = 0;

void task1() {
  for (int i = 0; i < 10000000; ++i) {
    std::lock(mtx1,
              mtx2);  // 如此使用同时上锁，排除两个线程上锁顺序不同导致死锁问题
    // mtx1.lock();
    // mtx2.lock();
    {
      globalVariable++;
      globalVariable--;
    }
    /*
     * @brief 导致死锁
     * 1. callFunc() throw error
     * 2. if () return;
     * 3. 两个线程上锁顺序不同，
     */
    mtx2.unlock();
    mtx1.unlock();
  }
}

void task2() {
  for (int i = 0; i < 1000; ++i) {
    mtx2.lock();
    mtx1.lock();
    {
      globalVariable++;
      globalVariable--;
    }
    mtx1.unlock();
    mtx2.unlock();
  }
}

int main() {
  std::thread t1(task1);
  std::thread t2(task2);

  t1.join();
  t2.join();

  std::cout << "current value is: " << globalVariable << std::endl;
}