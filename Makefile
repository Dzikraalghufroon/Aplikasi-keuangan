TARGET = main

CC = gcc
CFLAGS = -Wall -Wextra -Icontroller -Imodel -Iview -Iutils

SRC = \
    main.c \
    $(wildcard controller/*.c) \
    $(wildcard controller/*/*.c) \
    $(wildcard view/*.c) \
    $(wildcard view/*/*.c) \
    $(wildcard model/*.c) \
    $(wildcard model/*/*.c) \
    $(wildcard utils/*.c) \

OBJ = $(SRC:.c=.o)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET)

clean:
	rm -f $(TARGET) $(OBJ)
