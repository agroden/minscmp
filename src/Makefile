# main makefile
BIN=../bin
LIB=../lib
INC=../include

all: $(BIN)/drptool $(BIN)/minscmp

debug: MAKE += debug
debug: all

$(LIB)/libxyt.so:
	cd xytlib; $(MAKE)

$(LIB)/libdrp.so: $(LIB)/libxyt.so
	cd drplib; $(MAKE)

$(BIN)/drptool: $(LIB)/libdrp.so
	cd drptool; $(MAKE)

$(BIN)/minscmp: $(LIB)/libdrp.so
	cd minscmp; $(MAKE)

clean:
	@cd xytlib; make clean
	@cd drplib; make clean
	@cd drptool; make clean
	@cd minscmp; make clean
	$(RM) -rf $(BIN)
	$(RM) -rf $(LIB)
	$(RM) -rf $(INC)
