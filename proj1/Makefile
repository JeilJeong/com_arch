NAME = mips-sim
CC = gcc
CFLAGS = -Wall -Wextra -Werror
INCLUDES_DIR = ./includes
SRCS_DIR = ./srcs
SRCS = ft_main.c ft_check.c ft_bin2ass.c ft_syntax.c ft_type.c
OBJS = $(addprefix $(SRCS_DIR)/, $(SRCS:.c=.o))

all : $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

.c.o : 
	$(CC) $(CFLAGS) -I $(INCLUDES_DIR) -c $< -o $(<:.c=.o)

clean : 
	rm -rf $(OBJS) $(NAME)

re : clean all
