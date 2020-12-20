#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ft_reg.h"

unsigned int	*ft_reg(void)
{
	unsigned int	*ptr;

	if ((ptr = malloc(sizeof(unsigned int*) * REG_SIZE)) == NULL)
	{
		fputs("failed to allocate register in ft_reg\n", stderr);
		exit(1);
	}
	memset(ptr, 0x00, sizeof(unsigned int*) * REG_SIZE);
	return (ptr);
}
