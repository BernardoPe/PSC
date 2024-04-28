#!/bin/sh

#echo "------------------------------------------------------------------------"
#echo " - Testes com erros nos argumentos do programa"
#echo

./csv_filter 2>  /dev/null
if [ $? -ne 0 ]; then
	echo "[00] - OK"
else
	echo "[00] - Error"
	exit 1
fi

./csv_filter_ref -i -o output1.ref.csv 3 Lisboa -c 2>  /dev/null
if [ $? -ne 0 ]; then
	echo "[01] - OK"
else
	echo "[01] - Error"
	exit 1
fi

#echo "------------------------------------------------------------------------"
#echo " - Testes com redirecionamento"
#echo

./csv_filter_ref 3 Lisboa -c < input.csv > output1.ref.csv
./csv_filter 3 Lisboa -c < input.csv > output1.csv
cmp output1.ref.csv output1.csv

if [ $? -eq 0 ]; then
	echo "[10] - OK"
else
	echo "[10] - Error"
fi

rm output1.ref.csv output1.csv

#echo "------------------------------------------------------------------------"
#echo " - Testes com ficheiros na diretoria corrente"
#echo

./csv_filter_ref -i input.csv -o output1.ref.csv 3 Lisboa -c
./csv_filter -i input.csv -o output1.csv 3 Lisboa -c
cmp output1.ref.csv output1.csv

if [ $? -eq 0 ]; then
	echo "[20] - OK"
else
	echo "[20] - Error"
fi

rm output1.ref.csv output1.csv

./csv_filter_ref -i input.csv -o output1.ref.csv 3 Lisboa
./csv_filter -i input.csv -o output1.csv 3 Lisboa
cmp output1.ref.csv output1.csv

if [ $? -eq 0 ]; then
	echo "[21] - OK"
else
	echo "[21] - Error"
fi

rm output1.ref.csv output1.csv

#echo "------------------------------------------------------------------------"
#echo " - Testes com variável de ambiente"
#echo

mkdir -p subdir
cp input.csv subdir/inputx.csv
export CSV_FILTER_PATH=./subdir

./csv_filter_ref -i inputx.csv -o output1.ref.csv 3 Lisboa
./csv_filter -i inputx.csv -o output1.csv 3 Lisboa
cmp output1.ref.csv output1.csv
if [ $? -eq 0 ]; then
	echo "[30] - OK"
else
	echo "[30] - Error"
fi

rm output1.ref.csv output1.csv

unset CSV_FILTER_PATH
./csv_filter -i inputx.csv -o output1.csv 3 Lisboa 2> /dev/null
if [ $? -ne 0 ]; then
	echo "[31] - OK"
else
	echo "[31] - Error"
fi

rm -rf subdir

