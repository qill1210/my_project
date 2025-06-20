CXX = g++
CXXFLAGS := -std=c++17 -Wall -Wextra -g
CC = gcc
CFLAGS := -std=c11 -Wall -Wextra -g
LFLAGS =
OUTPUT	:= output
SRC		:= src
INCLUDE	:= include
LIB		:= lib
OBJ     := obj
LIBRARIES = -lglfw3dll -lglew32 -lopengl32 

ifeq ($(OS),Windows_NT)
MAIN	:= main.exe
SOURCEDIRS	:= $(SRC)
INCLUDEDIRS	:= $(INCLUDE)
LIBDIRS		:= $(LIB)
FIXPATH = $(subst /,\,$1)
RM			:= del /q /f
MD	:= mkdir
MKDIR_CMD = if not exist $(subst /,\,$1) $(MD) $(subst /,\,$1)
else
MAIN	:= main
SOURCEDIRS	:= $(shell find $(SRC) -type d)
INCLUDEDIRS	:= $(shell find $(INCLUDE) -type d)
LIBDIRS		:= $(shell find $(LIB) -type d)
FIXPATH = $1
RM = rm -f
MD = mkdir -p
MKDIR_CMD = $(MD) $1
endif

INCLUDES	:= $(patsubst %,-I%, $(INCLUDEDIRS:%/=%))
LIBS		:= $(patsubst %,-L%, $(LIBDIRS:%/=%))
SOURCES_CPP := $(wildcard $(patsubst %,%/*.cpp, $(SOURCEDIRS)))
SOURCES_C   := $(wildcard $(patsubst %,%/*.c, $(SOURCEDIRS)))
SOURCES     := $(SOURCES_CPP) $(SOURCES_C)
OBJECTS_CPP := $(patsubst $(SRC)/%.cpp,$(OBJ)/%.o,$(SOURCES_CPP))
OBJECTS_C   := $(patsubst $(SRC)/%.c,$(OBJ)/%.o,$(SOURCES_C))
OBJECTS     := $(OBJECTS_CPP) $(OBJECTS_C)
OUTPUTMAIN	:= $(call FIXPATH,$(OUTPUT)/$(MAIN))

all: $(OUTPUT) $(MAIN)

$(OUTPUT):
	$(call MKDIR_CMD,$@)

$(MAIN): $(OBJECTS) 
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $(OUTPUTMAIN) $(OBJECTS) $(LFLAGS) $(LIBRARIES) $(LIBS)

$(OBJ)/%.o: $(SRC)/%.c
	@$(call MKDIR_CMD,$(call FIXPATH,$(@D)))
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $(call FIXPATH,$@)

$(OBJ)/%.o: $(SRC)/%.cpp
	@$(call MKDIR_CMD,$(call FIXPATH,$(@D)))
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $(call FIXPATH,$@)

.PHONY: clean
clean:
	$(RM) $(OUTPUTMAIN)
ifeq ($(OS),Windows_NT)
	@if exist $(call FIXPATH,$(OBJ)) rd /s /q $(call FIXPATH,$(OBJ))
else
	@rm -rf $(OBJ)
endif
	@echo Cleanup complete!

run: all
	./$(OUTPUTMAIN)

