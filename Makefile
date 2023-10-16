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
	./$(EXECUTABLE)

$(EXECUTABLE): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@

input: $(EXECUTABLE)
	./$(EXECUTABLE) md5 -s -r "hello"

test: $(EXECUTABLE)
	./$(EXECUTABLE) md5
	./$(EXECUTABLE) md5 -s
	./$(EXECUTABLE) sha256 -s -r < input.txt
	./$(EXECUTABLE) sha256 < input.txt
	./$(EXECUTABLE) md5 -s -r -t "hello" < input.txt

# Compile each source file separately to generate object files
%.o: %.c
	$(CC) $(CFLAGS) -I./include -c $< -o $@

clean:
	rm -f $(OBJ) $(EXECUTABLE)

re: clean all
