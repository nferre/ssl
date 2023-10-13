#ifndef MD5_H
# define MD5_H

# define MD5_LENGTH 128 / 8 // md5 digest length in bytes

# define F(x, y, z) (((x) & (y)) | ((~x) & (z)))
# define G(x, y, z) (((x) & (z)) | ((y) & (~z)))
# define H(x, y, z) ((x) ^ (y) ^ (z))
# define I(x, y, z) ((y) ^ ((x) | (~z)))

# define A 0x67452301
# define B 0xefcdab89
# define C 0x98badcfe
# define D 0x10325476

void	md5(input_t	*node);
void	padding(input_t *node);
void	compute_md5(input_t *node);

#endif