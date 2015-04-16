#!/bin/bash
export LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH
EXE_NAME="java -cp .:bangdb.jar -Djava.library.path="."  testbangdb.TestMain"

echo "$EXE_NAME  $1 $2 $3 $4"
$EXE_NAME  $1 $2 $3 $4

