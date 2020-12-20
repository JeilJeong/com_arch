#include <unistd.h>
#include "ft_exec.h"

unsigned int	ft_if(void)
{
	//extract instruction;
	unsigned int	inst;
	int				type;

	inst = inst_mem[pc / 4];
	type = ft_istype(inst);
	//jump
	if (type == 0)
		ft_jtype(inst);
	else
		pc += 4;
	return (inst);
}

unsigned int	**ft_id(void)
{
	unsigned int	inst;
	unsigned int	**ret;
	int				type;
	
	inst = if_id->inst;
	type = ft_istype(inst);
	if (type == 2)
	{
		ret = ft_rtype(inst);
		return (ret);
	}
	else if (type == 1)
	{
		unsigned int	opcode_mask = 0xFC000000;
		unsigned int	opcode;
		
		opcode = inst & opcode_mask;
		ret = ft_itype(inst);
		if (opcode == 0x10000000)
		{
			//beq
			if (ret[0][2] == ret[0][3])
			{
				ft_pc_branch(ret[0][4]);
				branch = 1;
			}
		}
		else if(opcode == 0x14000000)
		{
			//bne
			if (ret[0][2] != ret[0][3])
			{
				ft_pc_branch(ret[0][4]);
				branch = 1;
			}
		}
		return (ret);
	}
	else
		return (ft_unknown(inst));
}

int	ft_ex(void)
{
	int	result;

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
			result = reg[id_ex->rs] + (int)id_ex->offset;
			return (result);
		case 0x30000000: //andi
			result = reg[id_ex->rs] & (int)id_ex->offset;
			return (result);
		case 0x34000000: //ori
			result = reg[id_ex->rs] | (int)id_ex->offset;
			return (result);
		case 0x28000000: //slti
			result = reg[id_ex->rs] < id_ex->offset;
			return (result);
		case 0x3C000000: //lui
			result = (int)id_ex->offset << 16;
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
			result = reg[id_ex->rs] + (int)id_ex->offset;
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
			//store
			data_mem[ex_mem->result / 4] = reg[ex_mem->rt];
	}
	return (0);
}

void	ft_wb(void)
{
	if (mem_wb->control[MEM_TO_REG] == 0)
	{
		if (mem_wb->control[REG_WRITE] == 1)
		{
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

void	ft_ff_insert(unsigned int inst, unsigned int **reg_control, int result, unsigned int mem_read)
{
	//MEM_WB
	mem_wb->rt = ex_mem->rt;
	mem_wb->rd = ex_mem->rd;
	mem_wb->result = ex_mem->result;
	mem_wb->mem_read = mem_read;
	for (int i = 0; i < 9; i++)
		mem_wb->control[i] = ex_mem->control[i];
	//EX_MEM
	ex_mem->rt = id_ex->rt;
	ex_mem->rd = id_ex->rd;
	ex_mem->result = result;
	for (int i = 0; i < 9; i++)
		ex_mem->control[i] = id_ex->control[i];
	//ID_EX: r-type
	if (reg_control[0][0] == 1)
	{
		id_ex->rs = reg_control[0][1];
		id_ex->rt = reg_control[0][2];
		id_ex->rd = reg_control[0][3];
		id_ex->funct = reg_control[0][4];
	}
	//ID_EX: i-type
	else if (reg_control[0][0] == 2)
	{
		id_ex->opcode = reg_control[0][1];
		id_ex->rs = reg_control[0][2];
		id_ex->rt = reg_control[0][3];
		id_ex->offset = reg_control[0][4];
	}
	for (int i = 0; i < 9; i++)
		id_ex->control[i] = reg_control[1][i];
	//IF_ID
	if_id->inst = inst;
}

void	ft_exec(int cycle)
{
	unsigned int	inst;
	unsigned int	**reg_control;
	int	result;
	unsigned int	mem_read;
	int				i;

	inst = 0;
	result = 0;
	mem_read = 0;
	reg_control = 0;
	i = 0;
	while (i < cycle)
	{
		ft_wb();
		mem_read = ft_mem();
		result = ft_ex();
		reg_control = ft_id();
		inst = ft_if();

		//forwarding
		if (branch == 1)
			inst = 0;
		ft_ff_insert(inst, reg_control, result, mem_read);
		//flip flop storing will be excuted last;
		//pc value will be decided when the branch or jmp is decoded;
		branch = 0;
		i++;
	}
}