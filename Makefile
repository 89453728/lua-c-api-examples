# debug mode enabled
CC := clang -g -Wall

CLIBS = -L /usr/local/lib/ -llua5.3
INC = -I /usr/local/include/lua-5.3/
CFLAGS := $(INC) $(CLIBS)
FILE := luacomplex.c

todo:
	$(CC) $(INC) -c $(FILE) -o $(patsubst %.c,%.o,$(FILE))
	$(CC) $(CLIBS) -shared -o $(patsubst %.c,%.so,$(FILE)) $(patsubst %.c,%.o,$(FILE))

.PHONY: todo clean

clean:
	@echo ".so and .o files were removed"
	@rm -rf *.so *.o
