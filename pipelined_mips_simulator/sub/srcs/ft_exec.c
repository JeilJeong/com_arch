#include <stdlib.h>
#include <pthread.h>

extern unsigned int		pc;
extern unsigned int		*inst_mem;
extern struct _IF_ID	IF_ID;

void	*ft_IF(void *data)
{
	int				index;
	unsigned int	inst;

	index = pc / 4;
	inst = inst_mem[index];
	IF_ID.inst = inst;
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
		if (pthread_create(&p_thread[0], NULL, ft_IF, (void *)NULL) < 0);
		{
			perror("thread create error : ");
			exit(0);
		}
		//ID
		if (pthread_create(&p_thread[1], NULL, ft_ID, (void *)NULL) < 0);
		{
			perror("thread create error : ");
			exit(0);
		}
		//EX
		if (pthread_create(&p_thread[2], NULL, ft_EX, (void *)NULL) < 0);
		{
			perror("thread create error : ");
			exit(0);
		}
		//MEM
		if (pthread_create(&p_thread[3], NULL, ft_MEM, (void *)NULL) < 0);
		{
			perror("thread create error : ");
			exit(0);
		}
		//WB
		if (pthread_create(&p_thread[4], NULL, ft_WB, (void *)NULL) < 0);
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