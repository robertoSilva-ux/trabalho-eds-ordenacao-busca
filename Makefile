CC = gcc
CFLAGS = -Wall -Wextra -O2 -std=c99 -D_GNU_SOURCE
LDFLAGS = 

OBJS = main.o placas.o cenarios.o ordenacao.o hash.o busca.o
TARGET = trab_eds

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

main.o: main.c placas.h cenarios.h ordenacao.h hash.h busca.h
placas.o: placas.c placas.h
cenarios.o: cenarios.c cenarios.h placas.h
ordenacao.o: ordenacao.c ordenacao.h placas.h
hash.o: hash.c hash.h placas.h
busca.o: busca.c busca.h placas.h hash.h

clean:
	rm -f *.o $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
