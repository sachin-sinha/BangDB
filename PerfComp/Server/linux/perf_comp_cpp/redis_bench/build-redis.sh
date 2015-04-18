#!/bin/sh

cd redis
make

cd ../hiredis
make

mv libhiredis.so libhiredis.so.0.13
ln -sf libhiredis.so.0.13 libhiredis.so
ln -sf libhiredis.so libhiredis.so.0

cd ../
