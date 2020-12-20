#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ft_mem.h"

unsigned int	*ft_inst_mem(void)
{
	unsigned int	*ptr;
	
	ptr = NULL;
	if ((ptr = malloc(sizeof(unsigned int) * MEM_SIZE)) == NULL)
	{
		fputs("failed to allocate instruction memory in ft_mem.c\n", stderr);
		exit(1);
	}
	memset(ptr, 0xFF, sizeof(unsigned int) * MEM_SIZE);
	return (ptr);
}

unsigned int	*ft_data_mem(void)
{
	unsigned int	*ptr;
	
	ptr = NULL;
	if ((ptr = malloc(sizeof(unsigned int) * MEM_SIZE)) == NULL)
	{
		fputs("failed to allocate instruction memory in ft_mem.c\n", stderr);
		exit(1);
	}
	memset(ptr, 0xFF, sizeof(unsigned int) * MEM_SIZE);
	return (ptr);
}
