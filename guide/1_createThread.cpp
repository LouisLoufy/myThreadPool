#include <iostream>
#include <thread>

void func(int a) {
  while (true) {
    // std::cout << "func thread" << std::endl;
    std::this_thread::sleep_for(std::chrono::microseconds(50));
  }
}

int main() {
  int a = 0;
  std::thread thread1(func, a);  // 创建线程并执行，在主线程退出时退出
  std::cout << "thread id is: " << thread1.get_id()
            << ", support num is: " << thread1.hardware_concurrency()
            << std::endl;
  /* 等待线程完成再去执行接下来的代码，主线程需要等待子线程结束之后才可以结束 */
  thread1.join();
  /* 让线程在后台运行，并且主线程不会等待子线程结束后再结束 */ 
  // thread1.detach();

  // while (true) {
  //     std::cout << "main thread" << std::endl;
  //     std::this_thread::sleep_for(std::chrono::microseconds(50));
  // }
}