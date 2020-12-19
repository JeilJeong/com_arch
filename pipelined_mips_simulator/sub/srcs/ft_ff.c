#include <stdio.h>
#include <stdlib.h>
#include "ft_ff.h"

IF_ID	*ft_if_id(void)
{
	IF_ID	*ptr;

	if (!(ptr = (IF_ID *)malloc(sizeof(IF_ID))))
	{
		perror("IF_ID malloc failed\n");
		exit(1);
	}
	return (ptr);
}

ID_EX	*ft_id_ex(void)
{
	ID_EX	*ptr;

	if (!(ptr = (ID_EX *)malloc(sizeof(ID_EX))))
	{
		perror("ID_EX malloc failed\n");
		exit(1);
	}
	return (ptr);
}

EX_MEM	*ft_ex_mem(void)
{
	EX_MEM	*ptr;

	if (!(ptr = (EX_MEM *)malloc(sizeof(EX_MEM))))
	{
		perror("EX_MEM malloc failed\n");
		exit(1);
	}
	return (ptr);
}

MEM_WB	*ft_mem_wb(void)
{
	MEM_WB	*ptr;

	if (!(ptr = (MEM_WB *)malloc(sizeof(MEM_WB))))
	{
		perror("MEM_WB malloc failed\n");
		exit(1);
	}
	return (ptr);
}