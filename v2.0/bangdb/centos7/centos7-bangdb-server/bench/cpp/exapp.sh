export LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH:lib

EXE_NAME=./bench
echo "$EXE_NAME  $1 $2 $3 $4"
$EXE_NAME  $1 $2 $3 $4
