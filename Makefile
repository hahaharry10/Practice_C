CC = clang
C89FLAGS = -std=c89
C99FLAGS = -std=c99
CFLAGS = -pedantic -g
HEADERS = *.h
MODULES = uint128.o
MAINS = 	c89Playground.o	test_uint128.o	__attribute__.o	memoryOverwriteBug.o	c99_combineDataTypes.o	c89_combineDataTypes.o	uncastedAllocation.o
TARGETS	=	c89Playground	test_uint128	__attribute__	memoryOverwriteBug		c99_combineDataTypes	c89_combineDataTypes	uncastedAllocation
.PHONY: all clean

all: ${TARGETS}

clean:
	rm ${TARGETS} ${MAINS} ${MODULES} *.o


c89Playground:					c89Playground.o
	$(CC) $(CFLAGS) $(C89FLAGS) -o $@ $^

__attribute__:					__attribute__.o ${MODULES}
	$(CC) $(CFLAGS) $(C99FLAGS) -o $@ $^

memoryOverwriteBug:				memoryOverwriteBug.o ${MODULES}
	$(CC) $(CFLAGS) $(C89FLAGS) -o $@ $^

c99_combineDataTypes:			c99_combineDataTypes.o ${MODULES}
	$(CC) $(CFLAGS) $(C99FLAGS) -o $@ $^

c89_combineDataTypes:			c89_combineDataTypes.o ${MODULES}
	$(CC) $(CFLAGS) $(C89FLAGS) -o $@ $^

test_uint128:					test_uint128.o ${MODULES}
	$(CC) $(CFLAGS) $(C89FLAGS) -o $@ $^

uncastedAllocation:				uncastedAllocation.o ${MODULES}
	$(CC) $(CFLAGS) $(C89FLAGS) -o $@ $^

%.o: %.c ${HEADERS}
	${CC} -c $(CFLAGS) ${C89FLAGS} -o $@ $<
