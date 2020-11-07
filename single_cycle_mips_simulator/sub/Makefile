NAME = mips-sim
CC = gcc
CFLAGS = 
INCLUDES_DIR = ./includes
SRCS_DIR = ./srcs
SRCS = ft_main.c ft_check.c ft_mem.c ft_reg.c ft_exec.c ft_type.c ft_print_result.c
OBJS = $(addprefix $(SRCS_DIR)/, $(SRCS:.c=.o))

all : $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

.c.o : 
	$(CC) $(CFLAGS) -I $(INCLUDES_DIR) -c $< -o $(<:.c=.o)

clean : 
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(NAME)

re : fclean all
