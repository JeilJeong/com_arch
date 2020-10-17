#ifndef FT_SYNTAX_H
# define FT_SYNTAX_H

unsigned char	ft_rs_mask(unsigned int buf);
unsigned char	ft_rt_mask(unsigned int buf);
unsigned char	ft_rd_mask(unsigned int buf);
unsigned short	ft_imm_mask(unsigned int buf);
unsigned short	ft_offset_mask(unsigned int buf);
unsigned int	ft_target_mask(unsigned int buf);
void	ft_type_1(unsigned int buf);
void	ft_type_2(unsigned int buf);
void	ft_type_3(unsigned int buf);
void	ft_type_4(unsigned int buf);
void	ft_type_5(unsigned int buf);
void	ft_type_6(unsigned int buf);
void	ft_type_7(unsigned int buf);
void	ft_type_8(unsigned int buf);
void	ft_type_9(unsigned int buf);
void	ft_type_10(unsigned int buf);
void	ft_type_11(unsigned int buf);
void	ft_type_12(unsigned int buf);
void	ft_type_13(unsigned int buf);
void	ft_type_14(unsigned int buf);
void	ft_type_15(unsigned int buf);
void	ft_syntax(unsigned int syntax_type, unsigned char *buffer);

#endif
