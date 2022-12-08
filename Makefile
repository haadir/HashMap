CXX=g++
CXXFLAGS=-g -Wall -std=c++11 
GTESTINCL := -I /usr/include/gtest/  
GTESTLIBS := -lgtest -lgtest_main  -lpthread
# Uncomment for parser DEBUG
#DEFS=-DDEBUG


all: ht-test str-hash-test hash-check boggle-driver 

boggle-driver: boggle.cpp boggle.h boggle-driver.cpp
	$(CXX) $(CXXFLAGS) $(DEFS) boggle.cpp boggle-driver.cpp -o $@

ht-test: ht-test.cpp ht.h
	$(CXX) $(CXXFLAGS) $(DEFS) $< -o $@

str-hash-test: str-hash-test.cpp hash.h
	$(CXX) $(CXXFLAGS) $(DEFS) $< -o $@

hash-check: hash-check.cpp hash.h
	$(CXX) $(CXXFLAGS) $(DEFS) $(GTESTINCL) $< -o $@ $(GTESTLIBS)

run-hash-check: hash-check
	valgrind --tool=memcheck --leak-check=yes ./hash-check

clean:
	rm -f *~ *.o ht-test ht-perf str-hash-test hash-check boggle-driver
