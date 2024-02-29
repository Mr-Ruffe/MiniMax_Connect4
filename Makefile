# Windows, g++(GCC) and sdl2 through MSYS2 mingw-w64

# SOURCE CODE
SRC_DIR = src

# FILE NAME
OBJ_NAME = play
BUILD_DIR = build/debug

# Windows GCC COMPILER
CC = g++

# COMPILATION FLAGS (options)
COMPILER_FLAGS = -std=c++17 -Wall -O0 -g

# SOURCE FILES
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)

# Windows INCLUDE_PATHS!
INCLUDE_PATHS = -Iinclude -IC:/msys64/ucrt64/include

# Windows LIBRARY_PATHS
LIBRARY_PATHS = -Llib -LC:/msys64/ucrt64/lib

# LINKER FLAGS
LINKER_FLAGS = 
# IF SDL2 is used; Windows LINKER_FLAGS!
LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf


all:
	@mkdir -p $(BUILD_DIR)/$(RESOURCE_DIR)
	@cp -r $(RESOURCE_DIR)/* $(BUILD_DIR)/$(RESOURCE_DIR)
	$(CC) $(COMPILER_FLAGS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(SRC_FILES) $(LINKER_FLAGS) -o $(BUILD_DIR)/$(OBJ_NAME)
