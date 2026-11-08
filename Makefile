CC = clang
CFLAGS = -Wall -Wextra -Iinclude
TARGET = hospeda
SOURCES = src/main.c src/cliente.c src/quarto.c src/historico.c src/reserva.c src/Espera.c

ifeq ($(OS),Windows_NT)
    EXE = .exe
    RUN = ./$(TARGET)$(EXE)
    RM = del /Q
else
    EXE =
    RUN = ./$(TARGET)
    RM = rm -f
endif

all: $(TARGET)$(EXE)

$(TARGET)$(EXE): $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET)$(EXE)

run: $(TARGET)$(EXE)
	$(RUN)

clean:
ifeq ($(OS),Windows_NT)
	-$(RM) $(TARGET)$(EXE) 2>NUL
else
	$(RM) $(TARGET)$(EXE)
endif

.PHONY: all run clean
