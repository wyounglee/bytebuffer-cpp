# Makefile for ByteBuffer

CC = g++
DEBUG = -g -fpermissive
WARN = -Wall
# Debug Flags
DBGFLAGS = $(DEBUG) $(WARN)
# Production Flags
PRODFLAGS = $(WARN)

TEST_H   = src/ByteBuffer.h
TEST_SRC = src/ByteBuffer.cpp src/test.cpp

PACKETS_H   = src/ByteBuffer.h
PACKETS_SRC = src/ByteBuffer.cpp src/examples/packets/packets.cpp

test: $(TEST_SRC) $(TEST_H)
	$(CC) $(DBGFLAGS) -o bin/$@ $(TEST_SRC)

packets: $(PACKETS_SRC) $(PACKETS_H)
	$(CC) $(DBGFLAGS) -o bin/$@ $(PACKETS_SRC)

clean:
	rm -f *.o bin/*.exe *~ \#*

macClean: clean
	rm -Rf *.dSYM
