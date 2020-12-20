#include <unistd.h>
#include "ft_exec.h"

unsigned int	ft_if(void)
{
	//extract instruction;
	unsigned int		inst;

	inst = inst_mem[pc / 4];
	printf("\npc : %u\n", pc);
	//calculate next pc value-> in while loop;
	return (inst);
}

unsigned int	**ft_id(void)
{
	unsigned int	inst;
	int				type;
	
	inst = if_id->inst;
	printf("*****************\ninst : %x\n*******************", inst);
	type = ft_istype(inst);
	if (type == 2)
		return (ft_rtype(inst));
	else if (type == 1)
		return (ft_itype(inst));
	// else if (type == 0)
	// 	ft_jtype(inst);
	// else
	// 	ft_unknown(inst);

		// case 0x10000000: //beq
		// 	if (reg[id_ex->rs] == reg[rt])
		// 		ft_pc_branch(reg, id_ex->offset);
		// 	else
		// 		ft_pc_normal(reg);
		// 	return (0);
		// case 0x14000000: //bne
		// 	if (reg[id_ex->rs] != reg[rt])
		// 		ft_pc_branch(reg, id_ex->offset);
		// 	else
		// 		ft_pc_normal(reg);
		// 	return (0);
	else
		return (ft_unknown(inst));
}

unsigned int	ft_ex(void)
{
	unsigned int	result;

	result = 0;
	if (id_ex->control[ALU_OP] == 2)
	{
		switch (id_ex->funct)
		{
		case 0x00: //nop
			return (result);
		case 0x20: //add
			result = reg[id_ex->rs] + reg[id_ex->rt];
			return (result);
		case 0x22: //sub
			result = reg[id_ex->rs] - reg[id_ex->rt];
			return (result);
		case 0x24: //and
			result = reg[id_ex->rs] & reg[id_ex->rt];
			return (result);
		case 0x25: //or
			result = reg[id_ex->rs] | reg[id_ex->rt];
			return (result);
		case 0x2A: //slt
			result = ((reg[id_ex->rs] < reg[id_ex->rt]) ? 1 : 0);
			return (result);
		default:
			return (result);
		}
	}
	else if (id_ex->control[ALU_OP] == 3)
	{
		switch (id_ex->opcode)
		{
		case 0x20000000: //addi
			result = reg[id_ex->rs] + id_ex->offset;
			return (result);
		case 0x30000000: //andi
			result = reg[id_ex->rs] & id_ex->offset;
			return (result);
		case 0x34000000: //ori
			result = reg[id_ex->rs] | id_ex->offset;
			return (result);
		case 0x28000000: //slti
			result = reg[id_ex->rs] < id_ex->offset;
			return (result);
		case 0x3C000000: //lui
			result = id_ex->offset << 16;
			return (result);
		default:
			return (result);
		}
	}
	else if (id_ex->control[ALU_OP] == 0)
	{
		switch (id_ex->opcode)
		{
		case 0x8C000000: //lw
		case 0xAC000000: //sw
			result = reg[id_ex->rs] + id_ex->offset - 0x10000000;
			return (result);
		default:
			return (result);
		}
	}
	return (result);
}

unsigned int	ft_mem(void)
{
	if (ex_mem->control[ALU_OP] == 0)
	{
		//load
		if (ex_mem->control[MEM_READ] == 1 && ex_mem->control[REG_WRITE] == 1)
			return (data_mem[ex_mem->result / 4]);
		else if (ex_mem->control[MEM_WRITE] == 1)
		{
			//store
			data_mem[ex_mem->result / 4] = reg[ex_mem->rt];
		}
	}
	return (0);
}

void	ft_wb(void)
{
	if (mem_wb->control[MEM_TO_REG] == 0)
	{
		printf("ft_wb == 0\n");
		if (mem_wb->control[REG_WRITE] == 1)
		{
			printf("ft_wb == 1\n");
			//r-type: ALU_OP = 2, dest = rd
			if (mem_wb->control[REG_DST] == 1)
				reg[mem_wb->rd] = mem_wb->result;
			//i-type: ALU_OP = 3, dest = rt
			else if(mem_wb->control[REG_DST] == 0)
				reg[mem_wb->rt] = mem_wb->result;
		}
	}
	//load: ALU_OP = 0, dest = rt
	else if (mem_wb->control[MEM_TO_REG] == 1 && mem_wb->control[REG_WRITE] == 1)
	{
		reg[mem_wb->rt] = mem_wb->mem_read;
	}
}

void	ft_ff_insert(unsigned int inst, unsigned int **reg_control, unsigned int result, unsigned int mem_read)
{
	write(1, " 10 ", 4);
	//MEM_WB
	mem_wb->rt = ex_mem->rt;
	mem_wb->rd = ex_mem->rd;
	mem_wb->result = ex_mem->result;
	mem_wb->mem_read = mem_read;
	for (int i = 0; i < 9; i++)
	{
		mem_wb->control[i] = ex_mem->control[i];
		printf("\nmem_wb control[%d]: %u\n", i, mem_wb->control[i]);
	}
	write(1, " 11 ", 4);
	//EX_MEM
	ex_mem->rt = id_ex->rt;
	ex_mem->rd = id_ex->rd;
	ex_mem->result = result;
	for (int i = 0; i < 9; i++)
	{
		ex_mem->control[i] = id_ex->control[i];
		printf("ex_mem control[%d]: %u\n", i, ex_mem->control[i]);
	}
	write(1, " 12 ", 4);
	char	tmp[3] = {' ', (char)reg_control[0][0] + 48, ' '};
	write(1, &tmp, 3);
	//ID_EX: r-type
	if (reg_control[0][0] == 1)
	{
		write(1, "\n+1+\n", 4);
		id_ex->rs = reg_control[0][1];
		id_ex->rt = reg_control[0][2];
		id_ex->rd = reg_control[0][3];
		id_ex->funct = reg_control[0][4];
		write(1, "\n+2+\n", 4);
	}
	//ID_EX: i-type
	else if (reg_control[0][0] == 2)
	{
		write(1, "\n+3+\n", 4);
		id_ex->opcode = reg_control[0][1];
		id_ex->rs = reg_control[0][2];
		id_ex->rt = reg_control[0][3];
		id_ex->offset = reg_control[0][4];
		write(1, "\n+4+\n", 4);
	}
	for (int i = 0; i < 9; i++)
	{
		id_ex->control[i] = reg_control[1][i];
		printf("id_ex control[%d]: %u\n", i, id_ex->control[i]);
	}
	write(1, " 13 ", 4);
	//IF_ID
	if_id->inst = inst;
	write(1, " 14 ", 4);
}

void	ft_exec(int cycle)
{
	unsigned int	inst;
	unsigned int	**reg_control;
	unsigned int	result;
	unsigned int	mem_read;
	int				i;

	inst = 0;
	result = 0;
	mem_read = 0;
	reg_control = 0;
	i = 0;
	while (i < cycle)
	{
		printf("1 ");
		ft_wb();
		printf("2 ");
		mem_read = ft_mem();
		printf("3 ");
		result = ft_ex();
		printf("4 ");
		reg_control = ft_id();
		printf("5 ");
		inst = ft_if();
		write(1, "6 ", 2);

		ft_ff_insert(inst, reg_control, result, mem_read);
		write(1, "7 ", 2);
		//flip flop storing will be excuted last;
		//pc value will be decided when the branch or jmp is decoded;
		pc += 4;
		printf("\n\n\n");
		i++;
	}
}