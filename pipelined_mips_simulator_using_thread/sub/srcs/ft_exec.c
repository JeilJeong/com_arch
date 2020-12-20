#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "ft_exec.h"
#include "ft_ff.h"

extern unsigned int		pc;
extern unsigned int		*inst_mem;
extern IF_ID			*if_id;
extern ID_EX			*id_ex;
extern EX_MEM			*ex_mem;
extern MEM_WB			*mem_wb;

void	*ft_if(void *data)
{
	int				index;
	unsigned int	*inst;

	if (!(inst = (unsigned int *)malloc(sizeof(unsigned int))))
	{
		perror("ft_if inst malloc failed\n");
		exit(1);
	}
	index = pc / 4;
	*inst = inst_mem[index];
	printf("here\n");
	return ((void *)inst);
}

// void	*ft_id(void *data)
// {
// 	int				type;
// 	unsigned int	inst;

// 	inst = if_id->inst;
// 	if (inst == 0)
// 		return ;
// 	type = ft_istype(inst);
// 	if (type == 2)
// 		return (ft_rtype(inst, reg, data_mem));
// 	else if (type == 1)
// 		return (ft_itype(inst, reg, data_mem));
// 	else if (type == 0)
// 		return (ft_jtype(inst, reg, data_mem));
// 	else
// 	{
// 		ft_nop();
// 		ft_pc_normal(reg);
// 		return (-1);
// 	}
// }

// void	*ft_ex(void *data)
// {
// }

// void	*ft_mem(void *data)
// {
// }

// void	*ft_wb(void *data)
// {
// }

void	ft_exec(int cycle)
{
	pthread_t		p_thread[5];
	int				i;
	unsigned int	inst;

	i = 0;
	while (i < cycle)
	{
		printf("??\n");
		//IF
		if (pthread_create(&p_thread[0], NULL, ft_if, (void *)NULL) < 0)
		{
			perror("thread create error : ");
			exit(0);
		}
		// //ID
		// if (pthread_create(&p_thread[1], NULL, ft_id, (void *)NULL) < 0);
		// {
		// 	perror("thread create error : ");
		// 	exit(0);
		// }
		// //EX
		// if (pthread_create(&p_thread[2], NULL, ft_ex, (void *)NULL) < 0);
		// {
		// 	perror("thread create error : ");
		// 	exit(0);
		// }
		// //MEM
		// if (pthread_create(&p_thread[3], NULL, ft_mem, (void *)NULL) < 0);
		// {
		// 	perror("thread create error : ");
		// 	exit(0);
		// }
		// //WB
		// if (pthread_create(&p_thread[4], NULL, ft_wb, (void *)NULL) < 0);
		// {
		// 	perror("thread create error : ");
		// 	exit(0);
		// }
		pthread_join(p_thread[0], (void *)&inst);
		// pthread_join(p_thread[1], (void *)&status);
		// pthread_join(p_thread[2], (void *)&status);
		// pthread_join(p_thread[3], (void *)&status);
		// pthread_join(p_thread[4], (void *)&status);

		//after join then filling the flip-flops
		if_id->inst = inst;
		printf("[%d] %u\n", i, if_id->inst);
		i++;
	}
}
