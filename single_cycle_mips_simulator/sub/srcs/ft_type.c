#include <stdio.h>
#include <stdlib.h>

int	ft_rtype(unsigned int inst, unsigned int *reg, unsigned int *inst_mem. unsigned int *data_mem)
{
	unsigned int	rs_mask = 0x3E00000;
	unsigned int	rt_mask = 0x1F0000;
	unsigned int	rd_mask = 0xF800;
	unsigned int	shamt_mask = 0x7C0;
	unsigned int	funct_mask = 0x3F;
	unsigned int	funct;

	funct = inst & funct_mask;
	switch(funct){
		case 32:
			;
		case 34:
			;
		case 37:
			;
		case 42:
			;
		default:
			//ft_nop();
	}
}

int	ft_itype(unsigned int inst, unsigned int *reg, unsigned int *inst_mem. unsigned int *data_mem)
{
	unsigned int	opcode_mask = 0xFC000000;
	unsigned int	rs_mask = 0x3E00000;
	unsigned int	rt_mask = 0x1F0000;
	unsigned int	imm_mask = 0xFFFF;
	unsigned int	opcode;

	opcode = inst & opcode_mask;

}

int	ft_jtype(unsigned int inst, unsigned int *reg, unsigned int *inst_mem. unsigned int *data_mem)
{
	unsigned int	add_mask = 0x3FFFFFF;
}

int	ft_istype(unsigned int inst)
{
	unsigned int	opcode_mask;
	unsigned int	type;

	opcode_mask = 0xFC000000;
	type = inst & opcode_mask;
	if (type == 0)
		return (2);
	else if (type == 8 /*addi*/|| \
			type == 12 /*andi*/|| \
			type == 13 /*ori */|| \
			type == 10 /*slti*/|| \
			type == 15 /*lui */|| \
			type == 35 /*lw  */|| \
			type == 43 /*sw  */|| \
			type == 4  /*beq */|| \
			type == 5  /*bne */)
		return (1);
	else if (type == 2)
		return (0);
	else
		return (-1);
}
