#include "ft_type.h"

int	ft_istype(unsigned int inst)
{
	unsigned int	opcode_mask;
	unsigned int	type;

	opcode_mask = 0xFC000000;
	type = inst & opcode_mask;
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