NAME = gl_project
EXT = .out
FNAME = $(NAME)$(EXT)

TEST_NAME = gl_project
TEST_EXT = .test
TEST_FNAME = $(TEST_NAME)$(TEST_EXT)

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
SRC_ALL_FILES=$(shell find $(SRC_DIR)/ -type f -name "*.cpp" )
OBJ_ALL_FILES=$(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_ALL_FILES))

SRC_EXE_FILES=$(filter-out $(SRC_DIR)/test.cpp, $(SRC_ALL_FILES))
OBJ_EXE_FILES=$(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_EXE_FILES))

SRC_TEST_FILES=$(filter-out $(SRC_DIR)/main.cpp,$(SRC_ALL_FILES))
OBJ_TEST_FILES=$(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_TEST_FILES))

$(OBJ_DIR)/%.o: %.cpp
	$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJ_EXE_FILES)
	$(CC) $(FLAGS) $(INCLUDES) -o $(BIN_DIR)/$(FNAME) $(OBJ_EXE_FILES) $(LIBS)

all: $(NAME)

test: $(OBJ_TEST_FILES)
	$(CC) $(FLAGS) $(INCLUDES) -o $(BIN_DIR)/$(TEST_FNAME) $(OBJ_TEST_FILES) $(LIBS)

clean:
	@rm -f $(OBJ_ALL_FILES)
	@echo "Objects deleted!"

fclean: clean
	@rm -f $(BIN_DIR)/$(FNAME)
	@rm -f $(BIN_DIR)/$(TEST_FNAME)
	@echo "Executable deleted!"

setup:
	@mkdir -p $(INC_DIR) $(INC_DIR)/controllers $(INC_DIR)/helpers $(INC_DIR)/models $(INC_DIR)/views
	@mkdir -p $(SRC_DIR) $(SRC_DIR)/controllers $(SRC_DIR)/helpers $(SRC_DIR)/models $(SRC_DIR)/views
	@mkdir -p $(OBJ_DIR) $(OBJ_DIR)/controllers $(OBJ_DIR)/helpers $(OBJ_DIR)/models $(OBJ_DIR)/views

re: fclean all