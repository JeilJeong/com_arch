#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ft_read.h"

extern unsigned int	*inst_mem;

void	ft_read(char *argv)
{
	FILE	*fd;
	int		size;
	int		count;
    //little endian to big endian
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