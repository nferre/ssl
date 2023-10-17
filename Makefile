CC = gcc
CFLAGS = -Wall -Werror -Wextra

SRC = src/ssl.c \
      src/parse/parse.c \
      src/parse/parse_utils.c \
      src/alg/md5.c \
      src/alg/hash_utils.c \
      src/alg/sha256.c

OBJ = $(SRC:.c=.o)

EXECUTABLE = ssl

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -I./include -c $< -o $@

clean:
	rm -f $(OBJ) $(EXECUTABLE)

re: clean all
