NAME = gl_project
EXT = .out
FNAME = $(NAME)$(EXT)

TEST_NAME = gl_project
TEST_EXT = .test
TEST_FNAME = $(TEST_NAME)$(TEST_EXT)

DEV_NAME = gl_project
DEV_EXT = .dev
DEV_FNAME = $(DEV_NAME)$(DEV_EXT)

CC = g++
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

SRC_ALL_FILES = $(shell find $(SRC_DIR)/ -type f -iname "*.cpp" )
OBJ_ALL_FILES = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_ALL_FILES))

SRC_BASE_FILES = $(shell find $(SRC_DIR)/ -type f \( -iname "*.cpp" ! -iwholename "$(SRC_DIR)/mains/*.cpp" \) )
OBJ_BASE_FILES = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_BASE_FILES))

SRC_EXE_FILES = $(SRC_BASE_FILES) $(SRC_DIR)/mains/main.cpp
OBJ_EXE_FILES = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_EXE_FILES))

SRC_TEST_FILES = $(SRC_BASE_FILES) $(SRC_DIR)/mains/test.cpp
OBJ_TEST_FILES = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_TEST_FILES))

SRC_DEV_FILES = $(SRC_BASE_FILES) $(SRC_DIR)/mains/dev.cpp
OBJ_DEV_FILES = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_DEV_FILES))

MAINS_DIR = $(SRC_DIR)/mains
MAINS_SRC = $(shell find $(MAINS_DIR) -type f -iname "*.cpp")
MAINS_OBJ = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(MAINS_SRC))

$(OBJ_DIR)/%.o: %.cpp
	$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJ_EXE_FILES)
	$(CC) $(FLAGS) $(INCLUDES) -o $(BIN_DIR)/$(FNAME) $(OBJ_EXE_FILES) $(LIBS)

all: $(NAME)

dev: $(OBJ_DEV_FILES)
	$(CC) $(FLAGS) $(INCLUDES) -o $(BIN_DIR)/$(DEV_FNAME) $(OBJ_DEV_FILES) $(LIBS)

test: $(OBJ_TEST_FILES)
	$(CC) $(FLAGS) $(INCLUDES) -o $(BIN_DIR)/$(TEST_FNAME) $(OBJ_TEST_FILES) $(LIBS)

clean:
	@rm -f $(OBJ_ALL_FILES)
	@echo "Objects deleted!"

fclean: clean
	@rm -f $(BIN_DIR)/$(FNAME)
	@rm -f $(BIN_DIR)/$(TEST_FNAME)
	@rm -f $(BIN_DIR)/$(DEV_FNAME)
	@echo "Executable deleted!"

setup:
	@mkdir -p $(INC_DIR) $(INC_DIR)/controllers $(INC_DIR)/helpers $(INC_DIR)/models $(INC_DIR)/views $(INC_DIR)/mains 
	@mkdir -p $(SRC_DIR) $(SRC_DIR)/controllers $(SRC_DIR)/helpers $(SRC_DIR)/models $(SRC_DIR)/views $(SRC_DIR)/mains 
	@mkdir -p $(OBJ_DIR) $(OBJ_DIR)/controllers $(OBJ_DIR)/helpers $(OBJ_DIR)/models $(OBJ_DIR)/views $(OBJ_DIR)/mains 

re: fclean all