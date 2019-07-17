CXX := g++
CXXFLAGS := -std=c++17 -O3 -Wall -Wextra -Werror
#CXXFLAGS := -std=c++17 -O0 -ggdb -Wall -Wextra -Werror
STRIP := strip
RM := rm

OUT := pub-sub
SRC := TopicContent.cpp Server.cpp main.cpp

OBJS := $(SRC:%.cpp=%.o)

.PHONY: all clean

all: $(OUT)

clean:
	$(RM) -f $(OBJS) $(OUT)

TopicContent.o: TopicContent.h
Server.o: Server.h TopicContent.h
main.o: Server.h

$(OUT): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(OUT) $(OBJS)
	$(STRIP) $(OUT)
