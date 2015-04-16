#!/bin/sh
export LD_LIBRARY_PATH=ext/bangdb:ext/leveldb:ext/bdb:$LD_LIBRARY_PATH

EXE_NAME="valgrind --tool=memcheck --track-origins=yes Debug/perf_comp"
echo "$EXE_NAME  $1 $2 $3 $4"
$EXE_NAME  $1 $2 $3 $4
