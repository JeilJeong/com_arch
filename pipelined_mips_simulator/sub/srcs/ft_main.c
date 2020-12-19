#include <stdio.h>
#include <stdlib.h>
#include "ft_check.h"
#include "ft_mem.h"
#include "ft_reg.h"
#include "ft_read.h"

//1) declare hardware;
unsigned int	*inst_mem;
unsigned int	*data_mem;
unsigned int	*reg;
unsigned int	*pc;
//1-1) need to make instance for IF_ID, etc by using structure;
unsigned int	*IF_ID;
unsigned int	*ID_EX;
unsigned int	*EX_MEM;
unsigned int	*MEM_WB;

int		main(int argc, char **argv)
{
	ft_arg_check(argc, argv);
	inst_mem = ft_inst_mem();
	data_mem = ft_data_mem();
	reg = ft_reg();
	ft_read(argv[1]);
	// ft_exec(atoi(argv[2]));
}