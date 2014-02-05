# main makefile
BIN=../bin
LIB=../lib
INC=../include
PRJS=xytlib drplib drptool minscmp

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
	@$(foreach prj,$(PRJS),cd $(prj); make clean;)
	$(RM) -rf $(BIN)
	$(RM) -rf $(LIB)
	$(RM) -rf $(INC)
