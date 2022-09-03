nasm -felf64 "../../basic_math_operations/Addition Algorithm/add.asm" -o add.o
g++ testing_software.cpp ../../basic_math_operations/basic_math_operations.cpp add.o -O3 -o "testing_software"
./testing_software
rm add.o
