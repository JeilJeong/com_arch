#include <stdlib.h>
#include <pthread.h>
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
	unsigned int	inst;

	index = pc / 4;
	inst = inst_mem[index];
	if_id->inst = inst;
}

void	*ft_id(void *data)
{
}

void	*ft_ex(void *data)
{
}

void	*ft_mem(void *data)
{
}

void	*ft_wb(void *data)
{
}

void	ft_exec(int cycle)
{
	pthread_t	p_thread[5];
	int			i;
	int			j;
	int			status;

	i = 0;
	while (i < cycle)
	{
		//IF
		if (pthread_create(&p_thread[0], NULL, ft_if, (void *)NULL) < 0);
		{
			perror("thread create error : ");
			exit(0);
		}
		//ID
		if (pthread_create(&p_thread[1], NULL, ft_id, (void *)NULL) < 0);
		{
			perror("thread create error : ");
			exit(0);
		}
		//EX
		if (pthread_create(&p_thread[2], NULL, ft_ex, (void *)NULL) < 0);
		{
			perror("thread create error : ");
			exit(0);
		}
		//MEM
		if (pthread_create(&p_thread[3], NULL, ft_mem, (void *)NULL) < 0);
		{
			perror("thread create error : ");
			exit(0);
		}
		//WB
		if (pthread_create(&p_thread[4], NULL, ft_wb, (void *)NULL) < 0);
		{
			perror("thread create error : ");
			exit(0);
		}
		j = 0;
		while (j < 4)
		{
			pthread_join(p_thread[j++], (void **)&status);
		}
		i++;
	}
}