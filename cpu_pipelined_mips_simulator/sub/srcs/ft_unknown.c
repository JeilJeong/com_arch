#include "ft_unknown.h"

unsigned int	*ft_unknown_ff(unsigned int flag, unsigned int rs, unsigned int rt, unsigned int rd)
{
	unsigned int	*tmp_reg;

	if (!(tmp_reg = (unsigned int *)malloc(sizeof(unsigned int) * UNKNOWN_TYPE_SIZE)))
	{
		perror("control malloc error");
		exit(1);
	}
	tmp_reg[0] = flag;
	tmp_reg[1] = rs;
	tmp_reg[2] = rt;
	tmp_reg[3] = rd;
	return (tmp_reg);
}

unsigned int	**ft_unknown(unsigned int inst)
{
	unsigned int	rs_mask = 0x3E00000;
	unsigned int	rt_mask = 0x1F0000;
	unsigned int	rd_mask = 0xF800;
	unsigned int	rs;
	unsigned int	rt;
	unsigned int	rd;
	unsigned int	flag;
	unsigned int	*tmp_reg;
	unsigned int	*control;
	unsigned int	**ret;

	flag = 4;
	rs = (inst & rs_mask) >> 21;
	rt = (inst & rt_mask) >> 16;
	rd = (inst & rd_mask) >> 11;
	if (!(ret = (unsigned int **)malloc(sizeof(unsigned int *) * 2)))
	{
		perror("ft_rtype return malloc failed\n");
		exit(1);
	}
	if (!(control = (unsigned int *)malloc(sizeof(unsigned int) * 9)))
	{
		perror("ft_rtype control malloc failed\n");
		exit(1);
	}
	tmp_reg = ft_unknown_ff(flag, rs, rt, rd);
	control[REG_DST] = 0;
	control[JUMP] = 0;
	control[BRANCH] = 0;
	control[MEM_READ] = 0;
	control[MEM_WRITE] = 0;
	control[MEM_TO_REG] = 0;
	control[ALU_OP] = 0;
	control[ALU_SRC] = 0;
	control[REG_WRITE] = 0;
	ret[0] = tmp_reg;
	ret[1] = control;
	return (ret);
}