.PHONY	= all bonus clean fclean re

HEADERS_PATH = ./includes/
SRCS_PATH = ./src/
OBJS_PATH = ./objs/
TEST_PATH = ./test
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -g3 -I $(HEADERS_PATH)
RM = rm -rf
MKDIR = mkdir -p
NAME = philo
SRC_FILES = main.c \
			init.c \
			error.c \
			philosophers.c \
			utils.c \

SOURCES = $(addprefix $(SRCS_PATH), $(SRC_FILES))
OBJ_FILES = $(patsubst %.c, %.o, $(SRC_FILES))
OBJECTS = $(addprefix $(OBJS_PATH), $(OBJ_FILES))
TESTS=$(wildcard $(TEST_PATH)/*.c)
TESTBINS = $(patsubst $(TEST_PATH)/%.c, $(TEST_PATH)/bin/%, $(TESTS))
OBJECTS_TEST = $(filter-out ./objs/main.o, $(OBJECTS))


all: $(NAME)

$(NAME): $(OBJECTS) 
	@$(CC) -o $(NAME) $(OBJECTS) -pthread

$(OBJS_PATH)%.o: $(SRCS_PATH)%.c
	@$(MKDIR) $(OBJS_PATH)
	@$(CC) $(CFLAGS) -c $< -o $@

$(TEST_PATH)/bin/%: $(TEST_PATH)/%.c
	@$(CC) $(CFLAGS) $< $(OBJECTS_TEST) -o $@  -lcriterion -lreadline
	
$(TEST_PATH)/bin:
	@$(MKDIR) $@

test: $(NAME) $(TEST_PATH)/bin $(TESTBINS)
	@for test in $(TESTBINS) ; do ./$$test --verbose ; done

bonus: all

clean:
	@$(RM) objs test/bin


fclean: clean
	@$(RM) $(NAME)

re: fclean all
