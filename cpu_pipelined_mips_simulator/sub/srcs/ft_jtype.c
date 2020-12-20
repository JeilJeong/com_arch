#include "ft_jtype.h"

void	ft_pc_jmp(int addr)
{
	unsigned int	pc_upper_mask = 0xF0000000;
	unsigned int	pc_upper;

	pc_upper = (pc + 4) & pc_upper_mask;
	pc = pc_upper + (addr << 2);
}

int		ft_jtype(unsigned int inst)
{
	unsigned int	opcode_mask = 0xFC000000;
	unsigned int	addr_mask = 0x3FFFFFF;
	unsigned int	opcode;
	unsigned int	addr;

	opcode = inst & opcode_mask;
	addr = inst & addr_mask;
	if (opcode == 0x08000000)
		ft_pc_jmp(addr);
	return (0);
}