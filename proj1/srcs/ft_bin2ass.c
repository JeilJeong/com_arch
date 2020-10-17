#include <stdio.h>
#include <stdlib.h>
#include "ft_bin2ass.h"
#include "ft_type.h"
#include "ft_syntax.h"

void	ft_parse2bit(unsigned char *buffer)
{
	unsigned char	opcode_mask = 252;
	unsigned char	funct_mask = 63;
	unsigned char	opcode = 0;
	unsigned char	funct = 0;

	opcode = (buffer[0] & opcode_mask) >> 2;
	if (opcode == 0)
	{
		funct = buffer[3] & funct_mask;
		ft_syntax(ft_rtype(funct), buffer);
	}
	else
	{
		ft_syntax(ft_istype(opcode), buffer);
	}
}

void	ft_bin2ass(FILE* fd)
{
	unsigned char	buffer[4];
	int		read_size = 0;
	int		flag = 0;
	int		i_inst = 0;

	while ((read_size = fread(buffer, sizeof(buffer), 1, fd)) > 0)
	{
		flag = 1;
		printf("inst %d: ", i_inst);
		i_inst++;	
		for (int i = 0; i < 4; i++)
			printf("%02x", buffer[i]);
		printf(" ");
		ft_parse2bit(buffer);
		printf("\n");
	}
	if (read_size <= 0 && flag == 0)
	{
		fputs("File empty error.", stderr);
		exit(1);
	}
}
