CXX = g++
CXXFLAGS = -std=c++17 -Wall -fdiagnostics-color=always -g -fanalyzer -fsanitize=address -fsanitize=leak -fsanitize=undefined -static-libasan
#change to whatever the includes are
INCLUDES = -Iinclude -I"$(shell pwd)" -Iinclude/boost_1_82_0
LIBSDIRS = -L./lib
LIBS = -lopengl32 -luser32 -lgdi32 -lshell32 -lglew32 -lglfw3dll# -lglfw3 
SRCS = $(wildcard *.cpp) $(wildcard */*.cpp) $(wildcard */*/*.cpp)
OBJS = $(SRCS:.cpp=.o)
EXEC = a_output
DEBUG = a_debug
DEBUGFLAGS = -std=c++17 -Wall -fdiagnostics-color=always -g -static-libgcc -static-libstdc++ -gdwarf-2
DEBUGOBJS = $(SRCS:.cpp=_debug.o)

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(LIBSDIRS) $(OBJS) $(LIBS) -static -o build/$(EXEC)
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@



debug: $(DEBUG)
$(DEBUG): $(DEBUGOBJS)
	$(CXX) $(DEBUGFLAGS) $(INCLUDES) $(LIBSDIRS) $(DEBUGOBJS) $(LIBS) -static -o build/$(DEBUG)
%_debug.o: %.cpp
	$(CXX) $(DEBUGFLAGS) $(INCLUDES) -c $< -o $@



clean:
	$(RM) $(OBJS) $(EXEC)
clean_debug:
	$(RM) $(DEBUGOBJS) $(DEBUG)