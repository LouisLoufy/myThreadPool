#include <iostream>
using namespace std;

class MyClass {
	int x; // 默认是private
};

struct MyStruct {
	int x; // 默认是public
};

int main() {
	MyStruct mystruct;
	mystruct.x = 20;

	MyClass myclass;
	// myclass.x = 20; //
	return 0;
}