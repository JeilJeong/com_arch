#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ft_print_result.h"

void	ft_print_reg(unsigned int *reg)
{
	for (int i = 0; i < 32; i++)
	{
		printf("$%d: 0x%08x\n", i, reg[i]);
	}
	printf("PC: 0x%08x\n", reg[32]);
}

void	ft_print_mem(char **argv, unsigned int *data_mem)
{
	int	addr;
	
	addr = strtol(argv[4], NULL, 16) - 0x10000000;
	for (int i = addr / 4; i < atoi(argv[5]); i++)
	{
		printf("0x%08x\n", data_mem[i]);
	}
}

void	ft_print_result(int argc, char **argv, unsigned int *reg, unsigned int *data_mem)
{
	if (argc == 3)
		return ;
	else if (strcmp(argv[3], "reg") == 0)
		ft_print_reg(reg);
	else if (strcmp(argv[3], "mem") == 0)
		ft_print_mem(argv, data_mem);
}
