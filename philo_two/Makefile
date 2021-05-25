NAME := philo_two

SRC := main.c \
	utils.c \
	sema.c \
	init.c \
	thread.c

OBJ := $(SRC:%.c=%.o)

CC := gcc
CFLAGS := -Wall -Wextra -Werror
# CFLAGS := -Wall -Wextra -Werror -g3
# LDFLAGS	:= -fsanitize=address

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(LDFLAGS) $^ -o $@

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm -rf $(OBJ)

fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY : all clean fclean re
.SILENT :