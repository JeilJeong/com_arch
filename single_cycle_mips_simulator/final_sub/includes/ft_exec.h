#ifndef FT_EXEC_H
# define FT_EXEC_H

unsigned int ft_curr_inst(unsigned int *buf, unsigned int pc);
void	*ft_read(char *argv, unsigned int *inst_mem);
int	ft_inst_exec(unsigned int inst, unsigned int *reg, unsigned int *data_mem);
void	ft_exec(char **argv, unsigned int *reg, unsigned int *inst_mem, unsigned int *data_mem);

#endif
