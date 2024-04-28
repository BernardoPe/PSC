#!/bin/sh

echo
echo "Testes do exercício 1"

cd exercicio1
./build.sh
./max_value_test

echo
echo "Testes do exercício 2"

cd ../exercicio2
./build.sh
./bits_test

echo
echo "Testes do exercício 3"

cd ../exercicio3
./build.sh
./string_split_test

echo
echo "Testes do exercício 4"

cd ../exercicio4
./build.sh
./string_to_time_test

echo
echo "Testes do exercício 5"

cd ../exercicio5
./build.sh
./test.sh

cd ..
