g++ -D_FILE_OFFSET_BITS=64 -Wall -O3 -operfcomp bench.cpp -lpthread -Lext/bangdb -lbangdb -Lext/bdb -ldb -Lext/leveldb -lleveldb
