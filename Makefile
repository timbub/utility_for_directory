CC = gcc
FLAGSDEBUG = -std=c11 -Wall -Wextra -Wconversion -Wshadow

TARGET      = mangen
OBJ         = mangen.o
SOURCE      = mangen.c
TEST_SCRIPT = test.sh

all:$(TARGET)
$(TARGET): $(OBJ)
	$(CC) $(OBJ) $(FLAGSDEBUG) -o $(TARGET)

$(OBJ): $(SOURCE)
	$(CC) $(SOURCE) $(FLAGSDEBUG) -c -o $(OBJ)

test: $(TARGET)
	./$(TEST_SCRIPT)

clean:
	rm -f $(TARGET) $(OBJ) actual_manifest.txt expected_manifest.txt -r test_dir

.PHONY: all clean test
