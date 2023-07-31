# 获取当前目录下所有的cpp文件
SRCS := $(wildcard *.cpp)

# 将cpp文件名称替换为可执行文件名称
EXES := $(patsubst %.cpp,%,$(SRCS))

# 设置编译器和编译选项
CXX := g++
CXXFLAGS := -Wall -O2 -std=c++2a
LIBS := -lpthread

# 默认目标为所有的可执行文件
all: $(EXES)

# 编译生成每个可执行文件
$(EXES): %: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@ $(LIBS)

# 清理生成的可执行文件
clean:
	rm -f $(EXES)