#ifndef FT_ITYPE_H
# define FT_ITYPE_H

# define I_TYPE_SIZE 5

extern unsigned int		pc;

void	ft_pc_branch(int imm);
unsigned int	*ft_itype_ff(unsigned int flag, unsigned int opcode, unsigned int rs, unsigned int rt, unsigned int offset);
unsigned int	**ft_itype(unsigned int inst);

#endif