CC = clang
CFLAGS = -Wall -Wextra -Iinclude
TARGET = hospeda
SOURCES = src/main.c src/cliente.c src/quarto.c

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all run clean
