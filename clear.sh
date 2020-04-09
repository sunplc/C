#!/bin/bash

# 删除 .out .o 扩展名的文件
find . -type f -name "*.out" -o -name "*.o"  | xargs rm -vf

# 删除没有扩展名的文件，排除.开头的隐藏文件和目录，排除 Makefile 文件
find . -type f ! -name  "*.*"  ! -name "*Makefile*"  -not -path '*/\.*' | xargs rm -vf

