#include <future>
#include <iostream>
#include <thread>

int task(int a, int b) {
  int retA = a * a;
  int retB = b * 2;
  return retA + retB;
}

int main() {
  // 默认为根据需要去选择是否创建线程
  std::future<int> fut = std::async(task, 1, 2);
  /* 异步执行, 开启一个线程去执行task */
  // std::future<int> fut = std::async(std::launch::async, task, 1, 2);
  /* 延时调用, 在需要get的时候再去执行task */
  // std::future<int> fut = std::async(std::launch::deferred, task, 1, 2);
  std::cout << "return value is: " << fut.get() << std::endl;
}