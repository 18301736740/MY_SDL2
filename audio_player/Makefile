CC = g++
#CFLAGS = -Wall -g -O0 -std=c++0x -shared -fpic
CFLAGS = -Wall -g -O0 -std=c++0x -lSDL2 -L ./lib -lavcodec -lavformat -lswscale -lavutil -lswresample
#PFLAGS = -rdynamic -ldl -std=c++0x -L ./ -ltest -Wl,--rpath=.
#SRC = operationfactory.cpp operationadd.cpp operationsub.cpp operationmul.cpp operationdvi.cpp
SRD = audio_player.cpp
#BIN = libtest.so
GIN = audio_player

$(GIN):$(BIN)
	$(CC) $(SRD) -o $(GIN) $(CFLAGS)
#$(BIN):$(SRC)
#	$(CC) $(SRC) -o $(BIN)  $(CFLAGS)

clean:
	$(RM) $(GIN) .*.sw?
