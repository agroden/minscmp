# make file for the minsec
PRJ=libdrp.so
OUT_DIR=../../lib
SRC=$(wildcard *.cpp)
OBJ=$(SRC:.cpp=.o)
LIB=libbozorth3.a
UNITTEST=
LD=g++
NBIS_LIB=/opt/NBIS/lib
CXXFLAGS=-Wall -std=c++11 -fPIC
LDFLAGS=-shared -L$(NBIS_DIR) -Wl,--whole-archive $(LIB) -Wl,--no-whole-archive


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
