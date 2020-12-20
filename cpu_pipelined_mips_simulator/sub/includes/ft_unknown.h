#ifndef FT_UNKNOWN_H
# define FT_UNKNOWN_H

#include <stdio.h>
#include <stdlib.h>
#include "ft_ff.h"
#include "ft_type.h"

# define UNKNOWN_TYPE_SIZE 4

unsigned int	*ft_unknown_ff(unsigned int flag, unsigned int rs, unsigned int rt, unsigned int rd);
unsigned int	**ft_unknown(unsigned int inst);

#endif