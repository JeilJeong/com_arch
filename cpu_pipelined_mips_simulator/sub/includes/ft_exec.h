#ifndef FT_EXEC_H
# define FT_EXEC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ft_ff.h"
#include "ft_type.h"
#include "ft_rtype.h"
#include "ft_itype.h"

extern unsigned int		*inst_mem;
extern unsigned int		*data_mem;
extern unsigned int		pc;
extern unsigned int		*reg;
extern IF_ID			*if_id;
extern ID_EX			*id_ex;
extern EX_MEM			*ex_mem;
extern MEM_WB			*mem_wb;

unsigned int	ft_if(void);
unsigned int	**ft_id(void);
unsigned int	ft_ex(void);
unsigned int	ft_mem(void);
void	ft_wb(void);
void	ft_exec(int cycle);

#endif