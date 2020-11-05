#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	ft_pc_jmp(unsigned int *reg, int addr)
{
	unsigned int	pc_upper_mask = 0xF0000000;
	unsigned int	pc_upper;

	pc_upper = (reg[32] + 4) & pc_upper_mask;
	reg[32] = pc_upper + (addr << 2);
}

void	ft_pc_branch(unsigned int *reg, int imm)
{
	reg[32] = (reg[32] + 4) + (imm << 2);
}

void	ft_pc_normal(unsigned int *reg)
{
	reg[32] += 4;
}

void	ft_nop(void)
{
	exit(1);
}

void	ft_rtype(unsigned int inst, unsigned int *reg, unsigned int *data_mem)
{
	unsigned int	rs_mask = 0x3E00000;
	unsigned int	rt_mask = 0x1F0000;
	unsigned int	rd_mask = 0xF800;
	//unsigned int	shamt_mask = 0x7C0;
	unsigned int	funct_mask = 0x3F;
	unsigned int	rs;
	unsigned int	rt;
	unsigned int	rd;
	//unsigned int	shamt;
	unsigned int	funct;

	rs = (inst & rs_mask) >> 21;
	rt = (inst & rt_mask) >> 16;
	rd = (inst & rd_mask) >> 11;
	//shamt = inst & shamt_mask;
	funct = inst & funct_mask;
	switch (funct)
	{
		case 0x00:
			ft_pc_normal(reg);
			break;
		case 0x20://add
			reg[rd] = reg[rs] + reg[rt];
			ft_pc_normal(reg);
			break;
		case 0x22://sub
			reg[rd] = reg[rs] - reg[rt];
			ft_pc_normal(reg);
			break;
		case 0x25://or
			reg[rd] = reg[rs] | reg[rt];
			ft_pc_normal(reg);
			break;
		case 0x2A://slt
			reg[rd] = ((reg[rs] < reg[rt]) ? 1 : 0);
			ft_pc_normal(reg);
			break;
		default:
			ft_nop();
			break;
	}
}

void	ft_itype(unsigned int inst, unsigned int *reg, unsigned int *data_mem)
{
	unsigned int	opcode_mask = 0xFC000000;
	unsigned int	rs_mask = 0x3E00000;
	unsigned int	rt_mask = 0x1F0000;
	unsigned int	imm_mask = 0xFFFF;
	unsigned int	rs;
	unsigned int	rt;
	int		imm;
	unsigned int	opcode;

	opcode = inst & opcode_mask;
	rs = (inst & rs_mask) >> 21;
	rt = (inst & rt_mask) >> 16;
	imm = (int)(inst & imm_mask);
	switch (opcode)
	{
		case 0x20000000://addi
			reg[rt] = reg[rs] + imm;
			printf("=====> reg[%d] : %x", rt, reg[rt]);
			ft_pc_normal(reg);
			break;
		case 0x30000000://andi
			reg[rt] = reg[rs] & imm;
			ft_pc_normal(reg);
			break;
		case 0x34000000://ori
			reg[rt] = reg[rs] | imm;
			ft_pc_normal(reg);
			break;
		case 0x28000000://slti
			reg[rt] = reg[rs] < imm;
			ft_pc_normal(reg);
			break;
		case 0x3C000000://lui
			reg[rt] = imm << 16;
			ft_pc_normal(reg);
			break;
		case 0x8C000000://lw
			write(1, "??\n", 3);
			reg[rt] = data_mem[(reg[rs] + imm - 0x10000000)/4];
			write(1, "??\n", 3);
			ft_pc_normal(reg);
			write(1, "??\n", 3);
			break;
		case 0xAC000000://sw
			write(1, "!!\n", 3);
			data_mem[(reg[rs] + imm - 0x10000000)/4] = reg[rt];
			write(1, "!!\n", 3);
			ft_pc_normal(reg);
			write(1, "!!\n", 3);
			break;
		case 0x10000000://beq
			if (reg[rs] == reg[rt])
			{
				printf("%X : %X\n", reg[rs], reg[rt]);
				write(1, "beq: branch in\n", 15);
				ft_pc_branch(reg, imm);
				write(1, "beq: branch out\n", 16);
			}
			else
			{
				printf("%X : %X\n", reg[rs], reg[rt]);
				write(1, "beq: else in\n", 13);
				ft_pc_normal(reg);
				write(1, "beq: else out\n", 14);
			}
			break;
		case 0x14000000://bne
			if (reg[rs] != reg[rt])
			{
				printf("%X : %X\n", reg[rs], reg[rt]);
				write(1, "bne: branch in\n", 15);
				ft_pc_branch(reg, imm);
				write(1, "bne: branch out\n", 16);
			}
			else
			{
				printf("%X : %X\n", reg[rs], reg[rt]);
				write(1, "bne: else in\n", 13);
				ft_pc_normal(reg);
				write(1, "bne: else out\n", 14);
			}
			break;
		default:
			ft_nop();
			break;
	}
}

void	ft_jtype(unsigned int inst, unsigned int *reg, unsigned int *data_mem)
{
	unsigned int	opcode_mask = 0xFC000000;
	unsigned int	addr_mask = 0x3FFFFFF;
	unsigned int	opcode;
	unsigned int	addr;

	opcode = inst & opcode_mask;
	addr = inst & addr_mask;
	if (opcode == 0x08000000)
		ft_pc_jmp(reg, addr);
	else
		ft_nop();
}

int	ft_istype(unsigned int inst)
{
	unsigned int	opcode_mask;
	unsigned int	type;

	opcode_mask = 0xFC000000;
	type = inst & opcode_mask;
	printf("\nistype: %X\n", type);
	if (type == 0x00000000)
		return (2);
	else if (type == 0x20000000 /*addi*/|| \
			type == 0x30000000 /*andi*/|| \
			type == 0x34000000 /*ori */|| \
			type == 0x28000000 /*slti*/|| \
			type == 0x3C000000 /*lui */|| \
			type == 0x8C000000 /*lw  */|| \
			type == 0xAC000000 /*sw  */|| \
			type == 0x10000000 /*beq */|| \
			type == 0x14000000 /*bne */)
		return (1);
	else if (type == 0x08000000)
		return (0);
	else
		return (-1);
}
