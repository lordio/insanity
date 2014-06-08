../bin/Linux/test: ModuleImpl.cpp testmain.cpp
  g++ -o ../bin/Linux/test -I../include -Wall -Wextra -std=gnu++11 `cd ../ && make -s echodeps && cd tests` testmain.cpp -L../bin/Linux -linsanity
  g++ -o ../bin/Linux/ConformanceTestModule.so -I../include -Wall -Wextra -std=gnu++11 -L../bin/Linux -linsanity -fPIC -shared `cd ../ && make -s echodeps && cd tests` ModuleImpl.cpp
  
run:
  LD_LIBRARY_PATH=../bin/Linux/:$$LD_LIBRARY_PATH ../bin/Linux/test
