#!/bin/sh
export LD_LIBRARY_PATH=ext/bangdb:ext/leveldb:ext/bdb:$LD_LIBRARY_PATH

EXE_NAME=./perfcomp
echo "$EXE_NAME  $1 $2 $3 $4"
$EXE_NAME  $1 $2 $3 $4
