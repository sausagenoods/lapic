CFLAGS=-Wall -Wmultichar
LDFLAGS=-lm

SRC=$(wildcard src/*.c)
TARGET=lapic

$(TARGET) : $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $@ $(LDFLAGS)

.PHONY: clean

clean:
	rm -f $(TARGET)
