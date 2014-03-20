CC=g++
CFLAGS=-Wall -Wextra -std=gnu++11 -fPIC -shared -lGL
DBGFLAGS=$(CFLAGS) -ggdb

#I think I should work out Gel++
all: gel.hpp gel.cpp
	$(CC) -o ../bin/Linux/libgel.so $(CFLAGS) gel.cpp

debug: gel.cpp gel.hpp
	$(CC) -o ../bin/Linux/libgel.so $(DBGFLAGS) gel.cpp

first:
	mkdir -p ../bin ../bin/Linux
clean:
	rm ../bin/Linux/libgel.so
	make first

rmtemp:
	rm -f ./*~

rebuild:
	make clean
	make all

echodeps:
	echo -lGL
