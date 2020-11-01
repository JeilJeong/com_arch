#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "ft_check.h"

void	ft_errno(int errno)
{
	if (errno == -1)
	{
		fputs("Not enough argument typed\n", stderr);
		exit(1);
	}
	else if (errno == -2)
	{
		fputs("File name greater than 255 character\n", stderr);
		exit(1);
	}
	else if (errno == -3)
	{
		fputs("3rd argument is not digit\n", stderr);
		exit(1);
	}
	else if (errno == -4)
	{
		fputs("4th argument is not both \"mem\" and \"reg\"\n", stderr);
		exit(1);
	}
	else if (errno == -5)
	{
		fputs("5th argument is not hexa decimal\n", stderr);
		exit(1);
	}
	else if (errno == -6)
	{
		fputs("6th argument is not decimal\n", stderr);
		exit(1);
	}
}

void	ft_arg_check(int argc, char **argv)
{
	if (argc < 4)
		ft_errno(-1);
	if (strlen(argv[1]) > 255)
		ft_errno(-2);
	for (unsigned long i = 0; i < strlen(argv[2]); i++)
	{
		if (!isdigit(argv[2][i]))
			ft_errno(-3);
	}
	if (strcmp(argv[3], "mem") == 0)
	{
		if (argc != 6)
			ft_errno(-1);
		if (strncmp(argv[4], "0x", 2) != 0)
			ft_errno(-5);
		for (unsigned long i = 2; i < strlen(argv[4]); i++)
		{
			if(!isxdigit(argv[4][i]))
				ft_errno(-5);
		}
		for (unsigned long i = 0; i < strlen(argv[5]); i++)
		{
			if (!isdigit(argv[5][i]))
				ft_errno(-6);
		}
	}
	else if (strcmp(argv[3], "reg") == 0)
		;
	else
		ft_errno(-4);
}
