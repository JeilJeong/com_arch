#include <stdio.h>
#include <stdlib.h>
#include "ft_check.h"

void	ft_errno(int errno)
{
	if (errno == -1)
	{
		printf("Not enough argument typed.\n");
		exit(1);
	}
	else if (errno == -2)
	{
		printf("File name greater than 255 character.\n");
		exit(1);
	}
}

void	ft_arg_check(int argc, char **argv)
{
	if (argc != 2)
		ft_errno(-1);
	else if(sizeof(argv[1]) > 255)
		ft_errno(-2);
}
