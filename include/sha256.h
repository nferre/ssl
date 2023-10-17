#ifndef SHA256_H
# define SHA256_H

# include "ssl.h"

# define H0 0x6a09e667
# define H1 0xbb67ae85
# define H2 0x3c6ef372
# define H3 0xa54ff53a
# define H4 0x510e527f
# define H5 0x9b05688c
# define H6 0x1f83d9ab
# define H7 0x5be0cd19

# define SHA256_LENGTH 256 / 8

#define ROTR(x,n)   (((x) >> n) | ((x) << (32 - n)))

void	sha256(input_t *node);
void	compute_sha256(input_t *node);

#endif