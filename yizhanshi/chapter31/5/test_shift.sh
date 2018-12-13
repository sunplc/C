#! /bin/sh

# 位置参数可以用shift命令左移，比如shift 3表示原来$4现在变成$1，原来的$5现在变成$2等等，原来的$1,$2,$3丢弃，$0不移动。不带参数的shift命令相当于shift 1。
echo "The program $0 is running"
echo "The first parameter is $1"
echo "The second parameter is $2"
echo "The parameter list is $@"

shift

echo "The program $0 is running"
echo "The first parameter is $1"
echo "The second parameter is $2"
echo "The parameter list is $@"
