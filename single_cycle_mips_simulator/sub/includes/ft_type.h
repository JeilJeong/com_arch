#ifndef FT_TYPE_H
# define FT_TYPE_H

void	ft_pc_jmp(unsigned int *reg, int addr);
void	ft_pc_branch(unsigned int *reg, int imm);
void	ft_pc_normal(unsigned int *reg);
void	ft_nop(void);
void	ft_rtype(unsigned int inst, unsigned int *reg, unsigned int *data_mem);
void	ft_itype(unsigned int inst, unsigned int *reg, unsigned int *data_mem);
void	ft_jtype(unsigned int inst, unsigned int *reg, unsigned int *data_mem);
int	ft_istype(unsigned int inst);

#endif
