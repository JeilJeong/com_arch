#ifndef FT_FF_H
# define FT_FF_H

typedef struct _IF_ID{
	unsigned int	inst;
} IF_ID;
typedef struct _ID_EX{
	unsigned char	rs;
} ID_EX;
typedef struct _EX_MEM{
	unsigned char	rs;
} EX_MEM;
typedef struct _MEM_WB{
	unsigned char	rs;
} MEM_WB;

IF_ID	*ft_if_id(void);
ID_EX	*ft_id_ex(void);
EX_MEM	*ft_ex_mem(void);
MEM_WB	*ft_mem_wb(void);

#endif