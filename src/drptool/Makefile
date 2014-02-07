# make file for drptool
PRJ=drptool
OUT_DIR=../../bin
SRC=$(wildcard *.cpp)
OBJ=$(SRC:.cpp=.o)
LIB=-ldrp
INC=-I$(CURDIR)/../../include
UNITTEST=
LD=g++
LIB_DIR=$(CURDIR)/../../lib
CXXFLAGS=-Wall -std=c++11
LDFLAGS=-Wl,-rpath=$(LIB_DIR) -L$(LIB_DIR)

all: $(OUT_DIR)/$(PRJ)

debug: CXXFLAGS += -g3 -DDEBUG
debug: all
ifdef
	@if [ -d $(UNITTEST) ]; then cd unittest; make debug; fi
endif

$(OUT_DIR)/$(PRJ): $(OBJ)
	@mkdir -p $(OUT_DIR)
	$(LD) $(LDFLAGS) $^ -o $@ $(LIB)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INC) -o $@ -c $<

clean:
	$(RM) -rf $(OBJ)
	$(RM) -rf $(OUT_DIR)/$(PRJ)
ifdef UNITTEST
	@if [ -d $(UNITTEST) ]; then cd unittest; make clean; fi
endif
