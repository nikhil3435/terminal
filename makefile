CC=gcc
DEPS = test.h
OBJ = built_in.o exec_rem.o prompt.o separate.o var_env.o main.o

%.o: %.c $(DEPS)
		$(CC) -c -o $@ $< $(CFLAGS)

shell: $(OBJ)
		gcc -o $@ $^ $(CFLAGS)
