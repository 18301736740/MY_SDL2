CC = g++
CFLAGS = -Wall -g -O0 -std=c++0x -shared -fpic
PFLAGS = -rdynamic -ldl -std=c++0x -L ./ -ltest -Wl,--rpath=.
SRC = operationfactory.cpp operationadd.cpp operationsub.cpp operationmul.cpp operationdvi.cpp
SRD = operationclient.cpp
BIN = libtest.so
GIN = test

$(GIN):$(BIN)
	$(CC) $(SRD) -o $(GIN) $(PFLAGS)
$(BIN):$(SRC)
	$(CC) $(SRC) -o $(BIN)  $(CFLAGS)

clean:
	$(RM) $(BIN) $(GIN) .*.sw?
