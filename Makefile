CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -fdiagnostics-color=always -g -Wno-unused-function -Wno-unused-variable
#change to whatever the includes are
INCLUDES = -Iinclude -I"$(shell pwd)" -Iinclude/boost_1_82_0
LIBSDIRS = -L./lib -L"C:\Program Files (x86)\Windows Kits\10\Lib\10.0.22000.0\um\x64"
LIBS = -lopengl32 -luser32 -lgdi32 -lshell32 -lglew32 -lglfw3dll# -lglfw3 
SRCS = $(wildcard *.cpp) $(wildcard */*.cpp) $(wildcard */*/*.cpp)
OBJS = $(SRCS:.cpp=.o)
EXEC = a_output

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(LIBSDIRS) $(OBJS) $(LIBS) -static -o build/$(EXEC)
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@
clean:
	$(RM) $(OBJS) $(EXEC)