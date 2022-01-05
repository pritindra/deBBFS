# deBBFS

#### Packages needed to be installed 
1. libfuse-dev
2. fuse library
3. libsqlite3-dev
4. sqlite3 library

#### Running and testing
compilation -
-> gcc -D_FILE_OFFSET_BITS=64 -I/usr/include/fuse -g -O2   -o bbfs bbfs.o log.o -lfuse -pthread -lcrypto -lssl -lsqlite3

to configure -
-> ./configure
    make

for logging the log file in another directory use command 
- tail -F bbfs.log

for unmounting the directory use command
- fusermount -u mountdir
#### Run in example directory
Run bbfs from root to mount dir -
../src/bbfs rootdir mountdir
    using compiled bbfs with arguements.
