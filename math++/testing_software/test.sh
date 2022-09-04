nasm -f elf64 "../../basic_math_operations/Addition Algorithm/add.asm" -o add.o
nasm -f elf64 "../../basic_math_operations/Subtraction Algorithm/subtract.asm" -o subtract.o
nasm -f elf64 "../../basic_math_operations/_assembly_strlen.asm" -o _assembly_strlen.o
g++ testing_software.cpp ../../basic_math_operations/basic_math_operations.cpp add.o subtract.o _assembly_strlen.o  -O3 -o "testing_software"
./testing_software
rm add.o