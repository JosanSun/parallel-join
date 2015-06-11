CC := gcc
TARGETS := ../a.out
LDLIBS := 
CCFLAGS := -MP -MMD -std=c11 -fopenmp

SRC := $(wildcard *.c)
OBJS := $(SRC:.c=.o)
DEPS := $(SRC:.c=.d)

all:$(TARGETS)

$(TARGETS): $(OBJS)
	$(CC) $(OBJS) $(LDLIBS) -o $(TARGETS)

%.o : %.c
	$(CC) -c $(CCFLAGS) $< -o $@

-include $(DEPS)

clean:
	rm -rf $(DEPS) $(OBJS)

.PHONY: clean
