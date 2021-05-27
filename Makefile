NAME = gl_project
EXT = .out
FNAME = $(NAME)$(EXT)

CC =  g++
FLAGS = -std=c++11 -Wall -Werror -Wextra
LIBS =

INC_DIR = include
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = .

#INCLUDES = -Iinclude
INCLUDES_DIR = $(shell find $(INC_DIR)/ -type d)
INCLUDES = $(patsubst %, -I%, $(INCLUDES_DIR))

vpath %.cpp src
vpath %.hpp include

# SRC_FILES=$(wildcard $(SRC_DIR)/*.cpp)
SRC_FILES=$(shell find $(SRC_DIR)/ -type f -name '*.cpp')
OBJ_FILES=$(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))

$(OBJ_DIR)/%.o: %.cpp
	$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJ_FILES)
	$(CC) $(FLAGS) $(INCLUDES) -o $(BIN_DIR)/$(FNAME) $(OBJ_FILES) $(LIBS)

all: $(NAME)

clean:
	@rm -f $(OBJ_FILES)
	@echo "Objects deleted!"

fclean: clean
	@rm -f $(BIN_DIR)/$(FNAME)
	@echo "Executable deleted!"

setup:
	@mkdir -p $(INC_DIR) $(INC_DIR)/controllers $(INC_DIR)/helpers $(INC_DIR)/models $(INC_DIR)/views
	@mkdir -p $(SRC_DIR) $(SRC_DIR)/controllers $(SRC_DIR)/helpers $(SRC_DIR)/models $(SRC_DIR)/views
	@mkdir -p $(OBJ_DIR) $(OBJ_DIR)/controllers $(OBJ_DIR)/helpers $(OBJ_DIR)/models $(OBJ_DIR)/views

re: fclean all