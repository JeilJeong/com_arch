#include <stdio.h>
#include <stdlib.h>
#include "ft_type.h"
#include "ft_rtype.h"

unsigned int	*ft_rtype_ff(unsigned int flag, unsigned int rs, unsigned int rt, unsigned int rd, unsigned int funct)
{
	unsigned int	*tmp_reg;

	if (!(tmp_reg = (unsigned int *)malloc(sizeof(unsigned int) * R_TYPE_SIZE)))
	{
		perror("control malloc error");
		exit(1);
	}
	tmp_reg[0] = flag;
	tmp_reg[1] = rs;
	tmp_reg[2] = rt;
	tmp_reg[3] = rd;
	tmp_reg[4] = funct;
	return (tmp_reg);
}

unsigned int	**ft_rtype(unsigned int inst)
{
	unsigned int	rs_mask = 0x3E00000;
	unsigned int	rt_mask = 0x1F0000;
	unsigned int	rd_mask = 0xF800;
	unsigned int	funct_mask = 0x3F;
	unsigned int	rs;
	unsigned int	rt;
	unsigned int	rd;
	unsigned int	funct;
	unsigned int	flag;
	unsigned int	*tmp_reg;
	unsigned int	*control;
	unsigned int	**ret;

	flag = 1;
	rs = (inst & rs_mask) >> 21;
	rt = (inst & rt_mask) >> 16;
	rd = (inst & rd_mask) >> 11;
	funct = inst & funct_mask;
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
	switch (funct)
	{
		case 0x00://nop
			tmp_reg = ft_rtype_ff(flag, rs, rt, rd, funct);
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
		case 0x20://add
		case 0x22://sub
		case 0x24://and
		case 0x25://or
		case 0x2A://slt
			tmp_reg = ft_rtype_ff(flag, rs, rt, rd, funct);
			control[REG_DST] = 1;
			control[JUMP] = 0;
			control[BRANCH] = 0;
			control[MEM_READ] = 0;
			control[MEM_WRITE] = 0;
			control[MEM_TO_REG] = 0;
			control[ALU_OP] = 2;
			control[ALU_SRC] = 0;
			control[REG_WRITE] = 1;
			ret[0] = tmp_reg;
			ret[1] = control;
			return (ret);
		default:
			tmp_reg = ft_rtype_ff(flag, rs, rt, rd, funct);
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
}