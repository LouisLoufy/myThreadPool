#include <functional>
#include <future>
#include <iostream>
#include <thread>

int task(int a, int b) {
  int retA = a * a;
  int retB = b * 2;
  return retA + retB;
}

int main() {
  std::packaged_task<int()> t(std::bind(task, 1, 2));
  t();
  std::cout << t.get_future().get() << std::endl;
}