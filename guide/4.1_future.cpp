/* 主线程获取子线程的返回值 */
#include <future>
#include <iostream>
#include <thread>

void task(int a, int b, std::promise<int>& p) {
  int retA = a * a;
  int retB = b * 2;

  p.set_value(retA + retB);
}

int main() {
  // 把promise和future做关联
  std::promise<int> p;
  std::future<int> f = p.get_future();

  std::thread t(task, 1, 2, std::ref(p));

  /* do something else */

  // get the promise value
  f.wait();
  // 注意：只能get一次
  std::cout << "return value is: " << f.get() << std::endl;

  t.join();
}