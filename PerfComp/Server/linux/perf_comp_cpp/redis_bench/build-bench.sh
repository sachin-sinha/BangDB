#!/bin/sh

gcc -std=c99 -D_FILE_OFFSET_BITS=64 -Wall -O3 -obench bench.c -lpthread -Lhiredis/ -lhiredis

