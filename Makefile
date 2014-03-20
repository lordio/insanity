CC=g++
LNK=ld
CFLAGS=-Iinclude -Wall -Wextra -c -std=gnu++11 -fPIC -ggdb
BUILDALLFLAGS=-Iinclude -Wall -Wextra -fPIC -std=gnu++11 -shared -lpthread -lX11 -Lbin/Linux -lgel -lGL
ALLSOURCE:=$(wildcard src/Linux/*.cpp) $(wildcard src/Generic/*.cpp) $(wildcard src/Default/*.cpp) $(wildcard experimental/*.cpp)
ALLOBJ:=$(patsubst src/%.cpp,obj/%.o,$(ALLSOURCE))

all: $(ALLOBJ) $(wildcard include/*)
	$(CC) -o bin/Linux/libinsanity.so $(BUILDALLFLAGS) $(ALLOBJ)

obj/Default/%.o: src/Default/%.cpp $(wildcard include/*)
	$(CC) -o $@ $< $(CFLAGS)

obj/Generic/%.o: src/Generic/%.cpp $(wildcard include/*)
	$(CC) -o $@ $< $(CFLAGS)

obj/Linux/%.o: src/Linux/%.cpp $(wildcard include/*)
	$(CC) -o $@ $< $(CFLAGS)

first:
	mkdir -p obj obj/Linux obj/Generic obj/Default bin/Linux
clean:
	rm -r obj
	rm bin/Linux/libinsanity.so
	make first

rmtemp:
	rm -f ./*~
	rm -f include/*~
	rm -f include/default/*~
	rm -f src/Default/*~
	rm -f src/Generic/*~
	rm -f src/Linux/*~

rebuild:
	make clean
	make all

echodeps:
	echo -lpthread -lX11 -lgel `cd gel && make -s echodeps && cd ..`
