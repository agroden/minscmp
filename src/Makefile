# make file for the minsec
PRJ=minscmp
OUT_DIR=bin
SRC=$(wildcard *.cpp)
OBJ=$(SRC:.cpp=.o)
UNITTEST=
LD=g++
CXXFLAGS=-Wall -std=c++11
LDFLAGS=

all: $(OUT_DIR)/$(PRJ)

debug: CXXFLAGS += -g3 -DDEBUG
debug: all
ifdef
	@if [ -d $(UNITTEST) ]; then cd unittest; make debug; fi
endif

$(OUT_DIR)/$(PRJ): $(OBJ)
	@mkdir -p $(OUT_DIR)
	$(LD) $(LDFLAGS) $^ -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INC) -o $@ -c $<

clean:
	$(RM) -rf $(OBJ)
	$(RM) -rf $(OUT_DIR)
ifdef UNITTEST
	@if [ -d $(UNITTEST) ]; then cd unittest; make clean; fi
endif
