#include <stdio.h>
#include <stdlib.h>
#include "ft_check.h"
#include "ft_mem.h"

int	main(int argc, char **argv)
{
	FILE		*fd;
	/*
	unsigned int	*inst_mem;
	unsigned int	*data_mem;

	inst_mem = ft_inst_mem();
	data_mem = ft_data_mem();
	for (int i = 0; i < MEM_SIZE; i++)
	{
		printf("%x", inst_mem[i]);
	}
	fputs("\n\n", stdout);
	for (int i = 0; i < MEM_SIZE; i++)
	{
		printf("%x", data_mem[i]);
	}
	fputs("\n\n", stdout);
	*/
	ft_arg_check(argc, argv);
	if ((fd = fopen(argv[1], "rb")) == NULL)
	{
		fputs("File open error\n", stderr);
		exit(1);
	}
	fclose(fd);
}
