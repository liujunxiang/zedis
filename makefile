CC := g++
CFLAGS := -g -Wall -DDEBUG
TARGET := ReidsProxy
SRCS := $(wildcard *.cpp)
OBJS := $(patsubst %cpp,%o,$(SRCS))
LIB=-lhiredis
LIBPATH=-L./lib
INCLUDE=-I./
all:$(TARGET)
$(OBJS):$(SRCS)
	$(CC) $(CFLAGS) -c  $^   $(INCLUDE)
$(TARGET):$(OBJS)
	$(CC)  -o $@ $^ $(LIB) $(LIBPATH)
clean:
	rm -rf $(TARGET) *.o