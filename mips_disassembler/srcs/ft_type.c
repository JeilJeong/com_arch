#include <stdio.h>
#include "ft_type.h"

unsigned int	ft_rtype(unsigned char funct)
{
	switch (funct)
	{
	case 0:
		printf("sll ");
		return 3;
	case 2:
		printf("srl ");
		return 3;
	case 3:
		printf("sra ");
		return 4;
	case 4:
		printf("sllv ");
		return 1;
	case 6:
		printf("srlv ");
		return 1;
	case 7:
		printf("srav ");
		return 13;
	case 8:
		printf("jr ");
		return 7;
	case 9:
		printf("jalr ");
		return 15;
	case 12:
		printf("syscall");
		return 10;
	case 16:
		printf("mfhi ");
		return 6;
	case 17:
		printf("mthi ");
		return 7;
	case 18:
		printf("mflo ");
		return 6;
	case 19:
		printf("mtlo ");
		return 7;
	case 24:
		printf("mult ");
		return 5;
	case 25:
		printf("multu ");
		return 5;
	case 26:
		printf("div ");
		return 5;
	case 27:
		printf("divu ");
		return 5;
	case 32:
		printf("add ");
		return 1;
	case 33:
		printf("addu ");
		return 1;
	case 34:
		printf("sub ");
		return 1;
	case 35:
		printf("subu ");
		return 1;
	case 36:
		printf("and ");
		return 1;
	case 37:
		printf("or ");
		return 1;
	case 38:
		printf("xor ");
		return 1;
	case 39:
		printf("nor ");
		return 1;
	case 42:
		printf("slt ");
		return 1;
	case 43:
		printf("sltu ");
		return 1;
	default:
		printf("unknown instruction");
		return 0;
	}
}

unsigned int	ft_istype(unsigned char opcode)
{
	switch (opcode)
	{
	case 2:
		printf("j ");
		return 9;
	case 3:
		printf("jal ");
		return 9;
	case 4:
		printf("beq ");
		return 14;
	case 5:
		printf("bne ");
		return 14;
	case 8:
		printf("addi ");
		return 2;
	case 9:
		printf("addiu ");
		return 2;
	case 10:
		printf("slti ");
		return 2;
	case 11:
		printf("sltiu ");
		return 2;
	case 12:
		printf("andi ");
		return 2;
	case 13:
		printf("ori ");
		return 2;
	case 14:
		printf("xori ");
		return 2;
	case 15:
		printf("lui ");
		return 12;
	case 32:
		printf("lb ");
		return 8;
	case 33:
		printf("lf ");
		return 8;
	case 35:
		printf("lw ");
		return 8;
	case 36:
		printf("lbu ");
		return 8;
	case 37:
		printf("lhu ");
		return 8;
	case 40:
		printf("sb ");
		return 8;
	case 41:
		printf("sh ");
		return 8;
	case 43:
		printf("sw ");
		return 8;
	default:
		printf("unknown instruction");
		return 0;
	}
}