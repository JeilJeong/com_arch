#include <stdio.h>
#include <stdlib.h>
#include "ft_check.h"
#include "ft_mem.h"
#include "ft_reg.h"
#include "ft_exec.h"
#include "ft_print_result.h"

int	main(int argc, char **argv)
{
	unsigned int	*inst_mem;
	unsigned int	*data_mem;
	unsigned int	*reg;

	inst_mem = ft_inst_mem();
	data_mem = ft_data_mem();
	reg = ft_reg();
	ft_arg_check(argc, argv);
	ft_exec(argc, argv, reg, inst_mem, data_mem);
	ft_print_result(argv, reg, data_mem);
	free(inst_mem);
	free(data_mem);
	free(reg);
}
