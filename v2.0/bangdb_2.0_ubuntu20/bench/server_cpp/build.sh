g++ -D_FILE_OFFSET_BITS=64 -Wall -O3 -obench src/bench.cpp -I/usr/local/include/bangdb-client -L/usr/local/lib -lbangdb-client-cpp -lbangdb-client

## for ssl use following
#g++ -D_FILE_OFFSET_BITS=64 -D_BANGDB_SSL_ -Wall -O3 -obench src/bench.cpp -I/usr/local/include/bangdb-client -L/usr/local/lib -lbangdb-client-cpp_s -lbangdb-client_s
