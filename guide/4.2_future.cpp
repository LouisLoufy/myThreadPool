/* 主线程获取子线程的返回值 */
#include <future>
#include <iostream>
#include <thread>

void task(int a, std::future<int>& b, std::promise<int>& p) {
  int retA = a * a;
  int retB = b.get() * 2;

  p.set_value(retA + retB);
}

int main() {
  // 把promise和future做关联
  std::promise<int> p_in;
  std::future<int> f_in = p_in.get_future();

  std::promise<int> p_ret;
  std::future<int> f_ret = p_ret.get_future();

  std::thread t(task, 1, std::ref(f_in), std::ref(p_ret));

  /* do something else */
  p_in.set_value(2);

  // get the promise value
  f_ret.wait();
  // 注意：只能get一次
  std::cout << "return value is: " << f_ret.get() << std::endl;

  t.join();
}