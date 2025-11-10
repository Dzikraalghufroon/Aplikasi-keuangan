TARGET = main

CC = gcc

CFLAGS = -Wall -Wextra -Icontroller -Imodel -Iview

SRC = main.c $(wildcard controller/*.c) $(wildcard view/*.c) $(wildcard model/*.c)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

# Untuak den nio test sebelum perubahan e nyo
test:
	$(CC) $(CFLAGS) main.c pos_anggaran.c transaksi.c -o $(TARGET)

# mambarasiahan file main
clean:
	rm -f $(TARGET)
