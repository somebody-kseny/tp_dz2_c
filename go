#!/bin/bash

# скрипт который был для запуска на своем компе

rm -r build
mkdir build
cmake -B build &&
cd build &&
make tests_gcovr_parall &&
make tests_gcovr_cons &&

make main_consistent &&
make main_parallel &&

cppcheck ../*.c &&
#тесты
valgrind --trace-children=yes --leak-check=full --show-leak-kinds=all --child-silent-after-fork=yes ./tests_gcovr_cons &&
valgrind --trace-children=yes --leak-check=full --show-leak-kinds=all --child-silent-after-fork=yes ./tests_gcovr_parall &&

gcovr -r .. .

cd ..

# стресс тест
echo "----"
gcc generate_long_input.c -o gen_rand &&
./gen_rand &&
echo "----"
echo "consistent:" > temp_output &&
./build/main_consistent long_input >> temp_output &&
echo "----" >> temp_output
echo "parallel:" >> temp_output
./build/main_parallel long_input >> temp_output &&
rm long_input
cat temp_output | grep time -B1
cat temp_output | grep output | awk '{print $2,$3}' | tr '\n' ' '| awk '$1 == $3 && $2 == $4 { print "----\nРезультат работы обеих программ одинаков"}'
rm temp_output
