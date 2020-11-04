#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned int ft_curr_inst(unsigned int *buf, unsigned int pc)
{
	unsigned int	index;

	index = pc / 4;
	return (buf[index]);
}

unsigned int	*ft_read(char *argv)
{
	unsigned int	*buf;
	FILE		*fd;
	int		size;
	int		count;

	if ((fd = fopen(argv, "rb")) == NULL)
	{
		fputs("ft_exec.c: File open error in ft_read\n", stderr);
		exit(1);
	}
	fseek(fd, 0, SEEK_END);
	size = ftell(fd);
	if ((buf = malloc(size)) == NULL)
	{
		fputs("ft_exec.c: Failed to allocate buf in ft_read\n", stderr);
		exit(1);
	}
	memset(buf, 0, size);
	fseek(fd, 0, SEEK_SET);
	if ((count = fread(buf, size, 1, fd)) <= 0)
	{
		fputs("ft_exec.c: Failed to read file int ft_read\n", stderr);
		exit(1);
	}
	fclose(fd);
	return (buf);
}

void	ft_inst_exec(unsigned int inst, unsigned int *reg, unsigned int *inst_mem, unsigned int *data_mem)
{
	//printf("%#.32X\n", inst);
	//type classification
	/*
	int	type;

	type = ft_istype(inst);
	if (type == 2)
	{
		puts("R-type");
		ft_rtype(inst, reg, inst_mem, data_mem);
	}
	else if (type == 1)
	{
		puts("I-type");
		ft_itype(inst, reg, inst_mem, data_mem);
	}
	else if (type == 0)
	{
		puts("J-type");
		ft_jtype(inst, reg, inst_mem, data_mem);
	}
	else
		puts("nop");
		;
	*/
}

void	ft_exec(int argc, char **argv, unsigned int *reg, unsigned int *inst_mem, unsigned int *data_mem)
{
	/*
	while문으로 N보다 작을 때까지 실행
	{
		instruction read function to 4byte 공간 - argument로 pc 값 넘겨줌
		instruction 분해 function - Itype, Rtype, Jtype으로 분류
		type별 instruction function 제시 - argument로 reg, mem을 받음, 실행 후 pc 계산
		instruction 한 개씩 실행
	}
	*/
	unsigned int	*buf;
	unsigned int	inst;
	int		N;
	int		i;

	N = atoi(argv[2]);
	i = 0;
	while (i < N)
	{
		buf = ft_read(argv[1]);
		inst = ft_curr_inst(buf, reg[32]);
		ft_inst_exec(inst, reg, inst_mem, data_mem);
		i++;
	}
}
