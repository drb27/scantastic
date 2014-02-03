ROOT=$(PWD)
export ROOT
CXX=g++
CXXFLAGS=-I./src -I/usr/include/cppunit -ggdb -std=c++11
LIBS=
MAIN_OBJS=src/scan.o src/handler.o
TEST_MODULES=$(wildcard src/tst/*.cpp)
TEST_OBJS=$(TEST_MODULES:.cpp=.o)
TEST_TARGETS=src/scan.o src/handler.o

ifdef COVERAGE
LIBS += -lgcov
CXXFLAGS += -fprofile-arcs -ftest-coverage -O0 -fno-inline
endif

dummy: bin/main

sources.d:
	tools/enumeratesources

%.d: %.cpp
	$(CXX) $(CXXFLAGS) -MF"$@" -MT"$@" -MT"$(@:.d=.o)" -MM $<

include sources.d
DEPS=$(SOURCES:.cpp=.d)
include $(DEPS)

bin/main: $(MAIN_OBJS)
	$(CXX) $(CXXFLAGS) $(MAIN_OBJS) $(LIBS) -o $@

test: $(TEST_OBJS) $(TEST_TARGETS)
	$(CXX) $(CXXFLAGS) $(TEST_OBJS) $(LIBS) $(TEST_TARGETS) -lcppunit -o $@
	rm TAGS
	etags src/*.cpp src/*.h src/tst/*.cpp src/tst/*.h

all: bin/main test
	./test

coverage: test
	./test
	cd cov; lcov --capture --output-file app.info -b $(CURDIR) --directory $(CURDIR)/src
	cd cov; lcov --remove app.info "/usr*" -o app.info
	cd cov; lcov --remove app.info "/src/tst*" -o app.info
	cd cov; genhtml app.info
	xdg-open cov/index.html &

docs: 
	rm -f -r doc/*
	doxygen
	xdg-open doc/html/index.html &

clean:
	rm -f synergi test
	rm -f -r cov/*
	find . -type f -name "*.o" -exec rm {} \;
	find . -type f -name "*.d" -exec rm {} \;
	find . -type f -name "*.gcda" -exec rm {} \;
	find . -type f -name "*.gcno" -exec rm {} \;

