CC = gcc
FLAGSDEBUG = -std=c11 -Wall -Wextra -Wconversion -Wshadow

TARGET = mangen
OBJ    = mangen.o
SOURCE = mangen.c

all:$(TARGET)
$(TARGET): $(OBJ)
	$(CC) $(OBJ) $(FLAGSDEBUG) -o $(TARGET)

$(OBJ): $(SOURCE)
	$(CC) $(SOURCE) $(FLAGSDEBUG) -c -o $(OBJ)
clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean
