/* 主线程设置值，多个子线程获取 */
#include <future>
#include <iostream>
#include <thread>

void task(int a, std::shared_future<int> b, std::promise<int>& p) {
  int retA = a * a;
  int retB = b.get() * 2;

  p.set_value(retA + retB);
}

int main() {
  // 把promise和future做关联
  std::promise<int> p_ret;
  // std::promise<int> p_ret2 = std::move(p_ret);
  std::future<int> f_ret = p_ret.get_future();
  
  std::promise<int> p_in;
  std::future<int> f_in = p_in.get_future();

  std::shared_future<int> s_f = f_in.share();

  std::thread t0(task, 1, s_f, std::ref(p_ret));
  std::thread t1(task, 1, s_f, std::ref(p_ret));
  std::thread t2(task, 1, s_f, std::ref(p_ret));

  /* do something else */
  p_in.set_value(2);
  s_f.wait();

  std::cout << "return value is: " << s_f.get() << std::endl;
  std::cout << "return value is: " << s_f.get() << std::endl;
  std::cout << "return value is: " << s_f.get() << std::endl;

  t0.join();
  t1.join();
  t2.join();
}