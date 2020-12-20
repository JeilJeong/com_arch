#include <stdio.h>
#include <stdlib.h>
#include "ft_type.h"
#include "ft_itype.h"

unsigned int	*ft_itype_ff(unsigned int flag, unsigned int opcode, unsigned int rs, unsigned int rt, unsigned int offset)
{
	unsigned int	*tmp_reg;

	if (!(tmp_reg = (unsigned int *)malloc(sizeof(unsigned int) * I_TYPE_SIZE)))
	{
		perror("control malloc error");
		exit(1);
	}
	tmp_reg[0] = flag;
	tmp_reg[1] = opcode;
	tmp_reg[2] = rs;
	tmp_reg[3] = rt;
	tmp_reg[4] = offset;
	return (tmp_reg);
}

unsigned int	**ft_itype(unsigned int inst)
{
	unsigned int	opcode_mask = 0xFC000000;
	unsigned int	rs_mask = 0x3E00000;
	unsigned int	rt_mask = 0x1F0000;
	unsigned int	imm_mask = 0xFFFF;
	unsigned int	rs;
	unsigned int	rt;
	unsigned int	logical_imm;
	int				arith_imm;
	unsigned int	flag;
	unsigned int	opcode;
	unsigned int	*tmp_reg;
	unsigned int	*control;
	unsigned int	**ret;

	flag = 2;
	opcode = inst & opcode_mask;
	rs = (inst & rs_mask) >> 21;
	rt = (inst & rt_mask) >> 16;
	logical_imm = inst & imm_mask;
	arith_imm = logical_imm;
	if ((arith_imm & 0x8000) == 0x8000)
	arith_imm |= 0xFFFF0000;
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
	switch (opcode)
	{
		case 0x20000000://addi
			tmp_reg = ft_itype_ff(flag, opcode, rs, rt, arith_imm);
			control[REG_DST] = 0;
			control[JUMP] = 0;
			control[BRANCH] = 0;
			control[MEM_READ] = 0;
			control[MEM_WRITE] = 0;
			control[MEM_TO_REG] = 0;
			control[ALU_OP] = 3;
			control[ALU_SRC] = 1;
			control[REG_WRITE] = 1;
			ret[0] = tmp_reg;
			ret[1] = control;
			return (ret);
		case 0x30000000://andi
			tmp_reg = ft_itype_ff(flag, opcode, rs, rt, logical_imm);
			control[REG_DST] = 0;
			control[JUMP] = 0;
			control[BRANCH] = 0;
			control[MEM_READ] = 0;
			control[MEM_WRITE] = 0;
			control[MEM_TO_REG] = 0;
			control[ALU_OP] = 3;
			control[ALU_SRC] = 1;
			control[REG_WRITE] = 1;
			ret[0] = tmp_reg;
			ret[1] = control;
			return (ret);
		case 0x34000000://ori
			tmp_reg = ft_itype_ff(flag, opcode, rs, rt, logical_imm);
			control[REG_DST] = 0;
			control[JUMP] = 0;
			control[BRANCH] = 0;
			control[MEM_READ] = 0;
			control[MEM_WRITE] = 0;
			control[MEM_TO_REG] = 0;
			control[ALU_OP] = 3;
			control[ALU_SRC] = 1;
			control[REG_WRITE] = 1;
			ret[0] = tmp_reg;
			ret[1] = control;
			return (ret);
		case 0x28000000://slti
			tmp_reg = ft_itype_ff(flag, opcode, rs, rt, arith_imm);
			control[REG_DST] = 0;
			control[JUMP] = 0;
			control[BRANCH] = 0;
			control[MEM_READ] = 0;
			control[MEM_WRITE] = 0;
			control[MEM_TO_REG] = 0;
			control[ALU_OP] = 3;
			control[ALU_SRC] = 1;
			control[REG_WRITE] = 1;
			ret[0] = tmp_reg;
			ret[1] = control;
			return (ret);
		case 0x3C000000://lui
			tmp_reg = ft_itype_ff(flag, opcode, rs, rt, logical_imm);
			control[REG_DST] = 0;
			control[JUMP] = 0;
			control[BRANCH] = 0;
			control[MEM_READ] = 0;
			control[MEM_WRITE] = 0;
			control[MEM_TO_REG] = 0;
			control[ALU_OP] = 3;
			control[ALU_SRC] = 1;
			control[REG_WRITE] = 1;
			ret[0] = tmp_reg;
			ret[1] = control;
			return (ret);
		case 0x8C000000://lw
			tmp_reg = ft_itype_ff(flag, opcode, rs, rt, arith_imm);
			control[REG_DST] = 0;
			control[JUMP] = 0;
			control[BRANCH] = 0;
			control[MEM_READ] = 1;
			control[MEM_WRITE] = 0;
			control[MEM_TO_REG] = 1;
			control[ALU_OP] = 0;
			control[ALU_SRC] = 1;
			control[REG_WRITE] = 1;
			ret[0] = tmp_reg;
			ret[1] = control;
			return (ret);
		case 0xAC000000://sw
			tmp_reg = ft_itype_ff(flag, opcode, rs, rt, arith_imm);
			control[REG_DST] = 0;
			control[JUMP] = 0;
			control[BRANCH] = 0;
			control[MEM_READ] = 0;
			control[MEM_WRITE] = 1;
			control[MEM_TO_REG] = 0;
			control[ALU_OP] = 0;
			control[ALU_SRC] = 1;
			control[REG_WRITE] = 0;
			ret[0] = tmp_reg;
			ret[1] = control;
			return (ret);
		case 0x10000000://beq
			tmp_reg = ft_itype_ff(flag, opcode, rs, rt, arith_imm);
			control[REG_DST] = 0;
			control[JUMP] = 0;
			control[BRANCH] = 1;
			control[MEM_READ] = 0;
			control[MEM_WRITE] = 0;
			control[MEM_TO_REG] = 0;
			control[ALU_OP] = 1;
			control[ALU_SRC] = 0;
			control[REG_WRITE] = 0;
			ret[0] = tmp_reg;
			ret[1] = control;
			return (ret);
		case 0x14000000://bne
			tmp_reg = ft_itype_ff(flag, opcode, rs, rt, arith_imm);
			control[REG_DST] = 0;
			control[JUMP] = 0;
			control[BRANCH] = 1;
			control[MEM_READ] = 0;
			control[MEM_WRITE] = 0;
			control[MEM_TO_REG] = 0;
			control[ALU_OP] = 1;
			control[ALU_SRC] = 0;
			control[REG_WRITE] = 0;
			ret[0] = tmp_reg;
			ret[1] = control;
			return (ret);
		default:
			tmp_reg = ft_itype_ff(flag, opcode, rs, rt, arith_imm);
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