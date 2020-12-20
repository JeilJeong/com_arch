#ifndef FT_RTYPE_H
# define FT_RTYPE_H

# define R_TYPE_SIZE 5

unsigned int	*ft_rtype_ff(unsigned int flag, unsigned int rs, unsigned int rt, unsigned int rd, unsigned int funct);
unsigned int	**ft_rtype(unsigned int inst);

#endif