CC = gcc
CFLAGS = -c -std=c99 -g
LDFLAGS = -g

SRC = ${wildcard ./src/*.c}
HDR = ${wildcard ./includes/*.h}
OBJ = ${SRC:.c=.o}
EXEC = yassine

all: ${SRC} ${OBJ} ${EXEC}

${EXEC}: ${OBJ}
	${CC} ${LDFLAGS} $^ -o $@

%.o: %.c ${HDR}
	${CC} ${CFLAGS} $< -o $@

install:
	make
	cp ./${EXEC} /usr/local/bin/yassine

clean:
	rm src/*.o ${EXEC}

