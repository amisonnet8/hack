YACC = bison -y -d
LEX = flex
CC := cc
CFLAGS += -std=c11 -Wall
LIBS =

TARGET = hack

SRCS := main.c code.c command.c symbol.c hack.c util.c heap.c y.tab.c lex.yy.c
OBJS := $(SRCS:.c=.o)
DEPS := $(OBJS:.o=.d)

all: $(TARGET)

-include $(DEPS)

$(TARGET) : $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@ $(LIBS)

test: $(TARGET)
	./test.sh

%.o: %.c
	$(CC) $(CFLAGS) -MMD -MP -c $<

hack.o: y.tab.h

y.tab.c y.tab.h: parse.y
	$(YACC) parse.y

lex.yy.c: lex.l
	$(LEX) lex.l

clean:
	rm -f $(TARGET) y.tab.c y.tab.h lex.yy.c *.d *.o test/actual/*.hack

.PHONY: all clean test
