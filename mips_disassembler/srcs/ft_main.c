#include <stdio.h>
#include <stdlib.h>
#include "ft_check.h"
#include "ft_bin2ass.h"

int	main(int argc, char **argv)
{
	FILE* fd;

	ft_arg_check(argc, argv);
	if ((fd = fopen(argv[1], "rb")) == NULL)
	{
		fputs("File open error", stderr);
		exit(1);
	}
	ft_bin2ass(fd);
	fclose(fd);
}
