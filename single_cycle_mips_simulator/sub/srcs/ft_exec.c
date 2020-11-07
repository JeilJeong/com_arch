#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ft_type.h"

unsigned int ft_curr_inst(unsigned int *inst_mem, unsigned int pc)
{
	unsigned int	index;

	index = pc / 4;
	//printf("\ncurrent inst: %X\n", inst_mem[index]);
	//printf("==>index = %u\n", index);
	return (inst_mem[index]);
}

void	*ft_read(char *argv, unsigned int *inst_mem)
{
	FILE		*fd;
	int		size;
	int		count;
	unsigned int	first_mask = 0xFF000000;
	unsigned int	second_mask = 0x00FF0000;
	unsigned int	third_mask = 0x0000FF00;
	unsigned int	fourth_mask = 0x000000FF;
	unsigned int	tmp_fourth;
	unsigned int	tmp_third;
	unsigned int	tmp_second;
	unsigned int	tmp_first;
	
	if ((fd = fopen(argv, "rb")) == NULL)
	{
		fputs("ft_exec.c: File open error in ft_read\n", stderr);
		exit(1);
	}
	fseek(fd, 0, SEEK_END);
	size = ftell(fd);
	fseek(fd, 0, SEEK_SET);
	if ((count = fread(inst_mem, size, 1, fd)) <= 0)
	{
		fputs("ft_exec.c: Failed to read file int ft_read\n", stderr);
		exit(1);
	}
	for (int i = 0; i < size; i++)
	{
		tmp_fourth = (inst_mem[i] & first_mask) >> 24;
		tmp_third = (inst_mem[i] & second_mask) >> 8;
		tmp_second = (inst_mem[i] & third_mask) << 8;
		tmp_first = (inst_mem[i] & fourth_mask) << 24;
		inst_mem[i] = tmp_first | tmp_second | tmp_third | tmp_fourth;
	}
	fclose(fd);
}

int	ft_inst_exec(unsigned int inst, unsigned int *reg, unsigned int *data_mem)
{
	int	type;

	type = ft_istype(inst);
	if (type == 2)
	{
	//	puts("R-type\n");
		return (ft_rtype(inst, reg, data_mem));
	}
	else if (type == 1)
	{
	//	puts("I-type\n");
		return (ft_itype(inst, reg, data_mem));
	}
	else if (type == 0)
	{
	//	puts("J-type\n");
		return (ft_jtype(inst, reg, data_mem));
	}
	else
	{
	//	puts("ft_nop\n");
		ft_nop();
		return (-1);
	}
}

void	ft_exec(int argc, char **argv, unsigned int *reg, unsigned int *inst_mem, unsigned int *data_mem)
{
	unsigned int	inst;
	int		n;
	int		i;

	n = atoi(argv[2]);
	i = 0;
	while (i < n)
	{
		ft_read(argv[1], inst_mem);
	//	printf("\npc ==> decimal: %d, hexa: %X\n", reg[32], reg[32]);
		inst = ft_curr_inst(inst_mem, reg[32]);
		if (ft_inst_exec(inst, reg, data_mem) < 0)
		{
			printf("i = %d\n", i);
			return ;
		}
		i++;
	}
}
