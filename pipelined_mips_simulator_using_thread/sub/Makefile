NAME = mips-sim
CC = gcc
CFLAGS =
INCLUDES_DIR = ./includes
SRCS_DIR = ./srcs
SRCS = ft_main.c ft_check.c ft_mem.c ft_reg.c ft_read.c ft_ff.c ft_exec.c
OBJS = $(addprefix $(SRCS_DIR)/, $(SRCS:.c=.o))

all : $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ -lpthread

.c.o : 
	$(CC) $(CFLAGS) -I $(INCLUDES_DIR) -c $< -o $(<:.c=.o)

clean : 
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(NAME)

re : fclean all