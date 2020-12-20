NAME = mips-sim
CC = gcc
CFLAGS = -Wall -Wextra -Werror
INCLUDES_DIR = ./includes
SRCS_DIR = ./srcs
SRCS = ft_main.c \
	ft_check.c \
	ft_mem.c \
	ft_reg.c \
	ft_read.c \
	ft_ff.c \
	ft_type.c \
	ft_rtype.c \
	ft_itype.c \
	ft_jtype.c \
	ft_exec.c \
	ft_print_result.c \
	ft_unknown.c
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