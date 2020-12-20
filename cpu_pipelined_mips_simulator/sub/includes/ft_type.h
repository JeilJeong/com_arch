#ifndef FT_TYPE_H
# define FT_TYPE_H

# define REG_DST 0
# define JUMP 1
# define BRANCH 2
# define MEM_READ 3
# define MEM_WRITE 4
# define MEM_TO_REG 5
# define ALU_OP 6
# define ALU_SRC 7
# define REG_WRITE 8

int	ft_istype(unsigned int inst);

#endif
