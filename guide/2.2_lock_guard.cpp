#include <iostream>
#include <mutex>
#include <thread>

std::mutex mtx;
int globalVariable = 0;

void task() {
  for (int i = 0; i < 1000; ++i) {
    /*
     * @brief
     * 模板类，自动管理锁和解锁，在构造时加锁，析构时释放锁
     * @note
     * 在定义lock_guard时会调用构造函数加锁
     * 在离开定义域的时候lock_guard会被销毁，调用析构函数中的解锁
     * @bug
     * 若定义域范围很小的话，锁的粒度会很大，很大的影响效率
     */
    // std::lock_guard<std::mutex> lock1(mtx);

    /*
     * @brief
     * 可以在需要的时候主动解锁等操作，并且会记录锁的状态
     * @note
     * 可以在尚未超出锁的作用域之前提前解锁
     * 在析构的时候会根据当前锁的状态是否解锁
     * @bug
     * unique_lock在内部会维护一个锁的状态，所以效率上比lock_guard慢
     */
    std::unique_lock<std::mutex> lock2(mtx);
    {
      globalVariable++;
      globalVariable--;
      lock2.unlock();
    }
  }
}

int main() {
  std::thread t(task);
  t.join();

  std::cout << "current value is: " << globalVariable << std::endl;
}
