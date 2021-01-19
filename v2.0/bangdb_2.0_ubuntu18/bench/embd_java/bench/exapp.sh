#!/bin/bash
export LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH:/usr/local/lib
EXE_NAME="java -cp .:../../../jars/bangdb-embd-java.jar -Djava.library.path="/usr/local/lib"  testbangdb.TestMain"

bash cleanup.sh
# args = <num_items> <num_threads>
# bash exapp.sh 100000 4
echo "$EXE_NAME  $1 $2"
$EXE_NAME  $1 $2

