CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic -Ofast
LFLAGS = -g
OBJS=bv.o grass.o field.o

all: grass

grass: $(OBJS)
	$(CC) $(LDFLAGS) -o grass $(OBJS)
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

tidy_objects:
	$(RM) $(OBJS)

tidy: tidy_objects

clean: tidy
	$(RM) grass
scan-build: clean
	scan-build --use-cc=clang make

# suggested by tutor Eric
format:
	clang-format -i -style=file *.[ch]
