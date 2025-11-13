TARGET = main

CC = gcc

CFLAGS = -Wall -Wextra -Icontroller -Imodel -Iview

SRC = main.c $(wildcard controller/*.c) $(wildcard view/*.c) $(wildcard controller/*/*.c) $(wildcard view/*/*.c) $(wildcard model/*/*.c) utils/utils.c utils/utils.h

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)


clean:
	rm -f $(TARGET)
