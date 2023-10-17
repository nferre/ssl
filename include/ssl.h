#ifndef SSL_H
# define SSL_H

# include "parse.h"
# include "md5.h"
# include "sha256.h"
# include <stdint.h>

void	compute_hash(void);
void	print_nodes(void);
void	free_nodes(void);

#endif