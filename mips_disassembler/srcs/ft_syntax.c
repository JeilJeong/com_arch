#include <stdio.h>
#include "ft_syntax.h"

unsigned char	ft_rs_mask(unsigned int buf)
{
	unsigned int	rs_mask = 0x3E00000;
	unsigned int	rs = 0;
	unsigned char	rs_return = 0;

	rs = (buf & rs_mask) >> 21;
	rs_return = (unsigned char)rs;
	return rs_return;
}

unsigned char	ft_rt_mask(unsigned int buf)
{
	unsigned int	rt_mask = 0x1F0000;
	unsigned int	rt = 0;
	unsigned char	rt_return = 0;

	rt = (buf & rt_mask) >> 16;
	rt_return = (unsigned char)rt;
	return rt_return;
}

unsigned char	ft_rd_mask(unsigned int buf)
{
	unsigned int	rd_mask = 0xF800;
	unsigned int	rd = 0;
	unsigned char	rd_return = 0;

	rd = (buf & rd_mask) >> 11;
	rd_return = (unsigned char)rd;
	return rd_return;
}

unsigned char	ft_sa_mask(unsigned int buf)
{
	unsigned int	sa_mask = 0x7C0;
	unsigned int	sa = 0;
	unsigned char	sa_return = 0;

	sa = (buf & sa_mask) >> 6;
	sa_return = (unsigned char)sa;
	return sa_return;
}

unsigned short	ft_imm_mask(unsigned int buf)
{
	unsigned int	imm_mask = 0xFFFF;
	unsigned int	imm = 0;
	unsigned short	imm_return = 0;

	imm = buf & imm_mask;
	imm_return = (unsigned short)imm;
	return imm_return;
}

unsigned short	ft_offset_mask(unsigned int buf)
{
	unsigned int	offset_mask = 0xFFFF;
	unsigned int	offset = 0;
	unsigned short	offset_return = 0;

	offset = buf & offset_mask;
	offset_return = (unsigned short)offset;
	return offset_return;
}

unsigned int	ft_target_mask(unsigned int buf)
{
	unsigned int	target_mask = 0x3FFFFFF;
	unsigned int	target_return = 0;

	target_return = buf & target_mask;
	return target_return;
}

void	ft_type_1(unsigned int buf)
{
	//opcode rs rt rd (0) funct
	//ex) add rd, rs, rt
	printf("$%u, ", ft_rd_mask(buf));
	printf("$%u, ", ft_rs_mask(buf));
	printf("$%u", ft_rt_mask(buf));
}

void	ft_type_2(unsigned int buf)
{
	//opcode rs rt imm
	//ex) addi rt, rs, imm
	printf("$%u, ", ft_rt_mask(buf));
	printf("$%u, ", ft_rs_mask(buf));
	printf("%d", (short)ft_imm_mask(buf));
}

void	ft_type_3(unsigned int buf)
{
	//opcode rs rt rd sa funct
	//ex) sll rd, rt, sa
	printf("$%u, ", ft_rd_mask(buf));
	printf("$%u, ", ft_rt_mask(buf));
	printf("%u", ft_sa_mask(buf));
}

void	ft_type_4(unsigned int buf)
{
	//opcode (0) rt rd sa funct
	//ex) sra rd, rt, sa
	printf("$%u, ", ft_rd_mask(buf));
	printf("$%u, ", ft_rt_mask(buf));
	printf("%u", ft_sa_mask(buf));
}

void	ft_type_5(unsigned int buf)
{
	//opcode rs rt (0) funct
	//ex) div rs, rt
	printf("$%u, ", ft_rs_mask(buf));
	printf("$%u", ft_rt_mask(buf));
}

void	ft_type_6(unsigned int buf)
{
	//opcode (0) rd (0) funct
	//ex) mfhi rd
	printf("$%u", ft_rd_mask(buf));
}

void	ft_type_7(unsigned int buf)
{
	//opcode rs (0) funct
	//ex) mthi rs
	printf("$%u", ft_rs_mask(buf));
}

void	ft_type_8(unsigned int buf)
{
	//opcode rs rt offset
	//ex) lb rt, offset(rs)
	printf("$%u, ", ft_rt_mask(buf));
	printf("%d", (short)ft_offset_mask(buf));
	printf("($%u)", ft_rs_mask(buf));
}

void	ft_type_9(unsigned int buf)
{
	//opcode target
	//ex) j target
	printf("%u", ft_target_mask(buf));
}

void	ft_type_10(unsigned int buf)
{
	//opcode (0) funct
	//ex) syscall
	buf = buf;
}

void	ft_type_11(unsigned int buf)
{
	//opcode rs (0) rd (0) funct
	//ex) jr rs
	printf("$%u", ft_rs_mask(buf));
}

void	ft_type_12(unsigned int buf)
{
	//opcode rs rt rd imm
	//ex) lui rt, imm
	printf("$%u, ", ft_rt_mask(buf));
	printf("%d", (short)ft_imm_mask(buf));
}

void	ft_type_13(unsigned int buf)
{
	//opcode rs rt rd (0) funct
	//ex) srav rd, rt, rs
	printf("$%u, ", ft_rd_mask(buf));
	printf("$%u, ", ft_rt_mask(buf));
	printf("$%u", ft_rs_mask(buf));
}

void	ft_type_14(unsigned int buf)
{
	//opcode rs rt rd offset
	//ex) beq rs, rt, offset
	printf("$%u, ", ft_rs_mask(buf));
	printf("$%u, ", ft_rt_mask(buf));
	printf("%d", (short)ft_offset_mask(buf));
}

void	ft_type_15(unsigned int buf)
{
	//opcode rs (0) rd (0) funct
	//ex) jalr rd, rs
	printf("$%u, ", ft_rd_mask(buf));
	printf("$%u", ft_rs_mask(buf));
}

void	ft_syntax(unsigned int syntax_type, unsigned char *buffer)
{
	unsigned int	buf;
	
	buf = 0;
	buf = buf + buffer[3];
	buf = buf + (buffer[2] << 8);
	buf = buf + (buffer[1] << 16);
	buf = buf + (buffer[0] << 24);
	switch (syntax_type)
	{
	case 1:
		ft_type_1(buf);
		return;
	case 2:
		ft_type_2(buf);
		return;
	case 3:
		ft_type_3(buf);
		return;
	case 4:
		ft_type_4(buf);
		return;
	case 5:
		ft_type_5(buf);
		return;
	case 6:
		ft_type_6(buf);
		return;
	case 7:
		ft_type_7(buf);
		return;
	case 8:
		ft_type_8(buf);
		return;
	case 9:
		ft_type_9(buf);
		return;
	case 10:
		ft_type_10(buf);
		return;
	case 11:
		ft_type_11(buf);
		return;
	case 12:
		ft_type_12(buf);
		return;
	case 13:
		ft_type_13(buf);
		return;
	case 14:
		ft_type_14(buf);
		return;
	case 15:
		ft_type_15(buf);
		return;
	default:
		return;
	}
}
