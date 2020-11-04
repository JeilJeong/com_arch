#ifndef FT_EXEC_H
# define FT_EXEC_H

unsigned int ft_curr_inst(unsigned int *buf, unsigned int pc);
unsigned int	*ft_read(char *argv);
void	ft_inst_exec(unsigned int inst, unsigned int *reg, unsigned int *inst_mem, unsigned int *data_mem);
void	ft_exec(int argc, char **argv, unsigned int *reg, unsigned int *inst_mem, unsigned int *data_mem);

#endif
