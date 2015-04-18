#!/bin/sh
export LD_LIBRARY_PATH=client-linux:$LD_LIBRARY_PATH
EXE_NAME=./bench
echo "$EXE_NAME $1 $2 $3"
$EXE_NAME $1 $2 $3
