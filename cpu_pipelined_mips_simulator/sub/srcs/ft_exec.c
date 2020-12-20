#include "ft_exec.h"

unsigned int	ft_if(void)
{
	//extract instruction;
	unsigned int		inst;

	inst = inst_mem[pc / 4];
	//calculate next pc value-> in while loop;
	return (inst);
}

unsigned int	**ft_id(void)
{
	unsigned int	inst;
	int				type;
	
	inst = if_id->inst;
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
	return (0);
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
		if (ex_mem->control[MEM_READ] == 1 && ex_mem->control[REG_WRITE] == 1)
			return (data_mem[ex_mem->alu_result / 4]);
		else if (ex_mem->control[MEM_WRITE] == 1)
		{
			data_mem[ex_mem->alu_result / 4] = reg[ex_mem->rt];
		}
	}
	return (0);
}

void	ft_wb(unsigned int data)
{
	if (mem_wb->control[MEM_TO_REG] == 0)
	{
		if (mem_wb->control[REG_WRITE] == 1)
		{
			//r-type: ALU_OP = 2, dest = rd
			if (mem_wb->control[REG_DST] == 1)
				reg[mem_wb->rd] = data;
			//i-type: ALU_OP = 3, dest = rt
			else if(mem_wb->control[REG_DST] == 0)
				reg[mem_wb->rt] = data;
		}
	}
	//load: ALU_OP = 0, dest = rt
	else if (mem_wb->control[MEM_TO_REG] == 1 && mem_wb->control[REG_WRITE] == 1)
	{
		reg[mem_wb->rt] = data;
	}
}

void	ft_exec(int cycle)
{
	unsigned int	inst;
	unsigned int	**reg_control;
	unsigned int	data;
	unsigned int	mem_read;
	int				i;

	inst = 0;
	data = 0;
	mem_read = 0;
	reg_control = 0;
	i = 0;
	while (i < cycle)
	{
		ft_wb(data);
		mem_read = ft_mem();
		data = ft_ex();
		reg_control = ft_id();
		inst = ft_if();
		//flip flop storing will be excuted last;
		//pc value will be decided when the branch or jmp is decoded;
	}
}