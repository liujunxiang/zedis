CC := g++
CFLAGS := -g -Wall
TARGET := ReidsProxy
SRCS := $(wildcard *.cpp)
OBJS := $(patsubst %cpp,%o,$(SRCS))
LIB=
INCLUDE=-I./
all:$(TARGET)
$(OBJS):$(SRCS)
	$(CC) $(CFLAGS) -c  $^  $(LIB) $(INCLUDE)
$(TARGET):$(OBJS)
	#ar -rc $@ $^
	$(CC)  -o $@ $^
clean:
	rm -rf $(TARGET) *.o