#!/bin/bash

if [ $# -ne 4 ]; then
	echo "invalid args [ <fromfile> <tofile> <numrec> <stopsec> ]"
	exit 1
fi

FILE=$1
ANOTHER_FILE=$2
NUMREC=$3
SLEEPSEC=$4
i=0
exec 4>> "$ANOTHER_FILE"

while IFS= read -ru 3 LINE; do
    echo "$LINE" >&4
    #echo "sent line $i"
    i=`expr $i + 1`

    if [ `expr $i % $NUMREC` -eq 0 ]; then
        echo "sent another $NUMREC, overall = $i"
    fi
    if [ `expr $i % $NUMREC` -eq 0 ]; then
        sleep $SLEEPSEC
    fi
done 3< "$FILE"
