#ifndef FT_FF_H
# define FT_FF_H

typedef struct _IF_ID{
	unsigned int	inst;
} IF_ID;

typedef struct _ID_EX{
	unsigned int	opcode;
	unsigned int	rs;
	unsigned int	rt;
	unsigned int	rd;
	unsigned int	funct;
	unsigned int	offset;
	//control
	unsigned int	control[9];
} ID_EX;

typedef struct _EX_MEM{
	unsigned int	rt;
	unsigned int	rd;
	int	result;
	//control
	unsigned int	control[9];
} EX_MEM;

typedef struct _MEM_WB{
	unsigned int	rt;
	unsigned int	rd;
	int	result;
	unsigned int	mem_read;
	//control
	unsigned int	control[9];
} MEM_WB;

IF_ID	*ft_if_id(void);
ID_EX	*ft_id_ex(void);
EX_MEM	*ft_ex_mem(void);
MEM_WB	*ft_mem_wb(void);

#endif