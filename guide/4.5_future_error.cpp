#include <future>
#include <iostream>

void test(std::promise<int>& para) {
  para.set_value(10);
  // para.set_value(20);
  return;
}

int main() {
  std::promise<int> pro;
  std::future<int> T = pro.get_future();
  std::thread fun(test, std::ref(pro));
  fun.join();
  std::cout << T.get() << std::endl;
  // 在调用get()后，共享状态就已经解除了，这时的get_future就是无效行为
  auto Error_T = pro.get_future();
  return 0;
}