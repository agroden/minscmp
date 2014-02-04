# make file for the minsec
PRJ=libxyt.so
OUT_DIR=../../lib
OUT_INC_DIR=../../include
OUT_INC=xyt.h
SRC=$(wildcard *.cpp)
OBJ=$(SRC:.cpp=.o)
LIB=
INC=
UNITTEST=
LD=g++
CXXFLAGS=-Wall -std=c++11 -fPIC
LDFLAGS=-shared

all: $(OUT_DIR)/$(PRJ)

debug: CXXFLAGS += -g3 -DDEBUG
debug: all
ifdef
	@if [ -d $(UNITTEST) ]; then cd unittest; make debug; fi
endif

$(OUT_DIR)/$(PRJ): $(OBJ)
	@mkdir -p $(OUT_DIR)
	$(LD) $(LDFLAGS) $(OBJ) -o $@ $(LIB)
	@mkdir -p $(OUT_INC_DIR)
	@cp $(OUT_INC) $(OUT_INC_DIR)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INC) -o $@ -c $<

clean:
	$(RM) -rf $(OBJ)
	$(RM) -rf $(OUT_DIR)/$(PRJ)
ifdef UNITTEST
	@if [ -d $(UNITTEST) ]; then cd unittest; make clean; fi
endif
