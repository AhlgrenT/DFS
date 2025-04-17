#Compiler & flags
CC = g++
CFLAGS = -Wall -g

#Directories
SRC_DIR = src
BUILD_DIR = build
BIN_DIR = bin

#Files
SRC = 

# Rule to compile main.cpp to main.o
main.o:
	g++ -Wall -g -c master/main.cpp -o main.o

# Rule to link object files and create the executable
DFS: main.o
	g++ -Wall main.o -o DFS

# Clean target: remove object files and the executable
clean:
	rm -f main.o dfs.o DFS

# Phony target for clean
.PHONY: clean
