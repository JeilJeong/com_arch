#ifndef FT_PRINT_RESULT_H
# define FT_PRINT_RESULT_H

extern unsigned int		*data_mem;
extern unsigned int		pc;
extern unsigned int		*reg;

void	ft_print_reg(void);
void	ft_print_mem(char **argv);
void	ft_print_result(int argc, char **argv);

#endif