#include "ssl.h"

uint32_t S[] = {7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20,
4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21};

uint32_t K[] = {0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391};

uint32_t rotate_left(uint32_t x, uint32_t n)
{
	return (x << n) | (x >> (32 - n));
}

void	md5(input_t *node)
{
	// padding
	for (uint64_t i = 0; i < (node->total_length - (node->data_length + 8 % 64)); i++)
		*(uint8_t*)(node->data + node->data_length + i) = (i == 0) ? 128 : 0;
	
	// add length end of block
	*(uint32_t *)(node->data + node->total_length - 8) = (uint32_t)(node->data_length * 8);
	*(uint32_t *)(node->data + node->total_length - 4) = (uint32_t)((node->data_length * 8) >> 32);
	
	compute_md5(node);
}


// some cccccrazy computations
void	compute_md5(input_t *node)
{
	uint32_t digest[4] = {A, B, C, D};

	// for each 64 bytes block
	for (int block = 0; block < node->total_length; block += 64) // for each block (512 bits)
	{
		uint32_t input[16];
		
		// 64 byte block to 16 32 bites block
		for (int i = 0; i < 16; i++)
			input[i] = *(uint32_t *)(node->data + block + i * 4);

		uint32_t AA = digest[0];
		uint32_t BB = digest[1];
		uint32_t CC = digest[2];
		uint32_t DD = digest[3];
		uint32_t E;
		uint32_t j;

		for (int i = 0; i < 64; i++)
		{
			if (i < 16)
			{
				E = F(BB, CC, DD);
				j = i;
			}
			else if (i < 32)
			{
				E = G(BB, CC, DD);
				j = ((i * 5) + 1) % 16;
			}
			else if (i < 48)
			{
				E = H(BB, CC, DD);
				j = ((i * 3) + 5) % 16;
			}
			else if (i < 64)
			{
				E = I(BB, CC, DD);
				j = (i * 7) % 16;
			}


			uint32_t temp = DD;
			DD = CC;
			CC = BB;
			BB = BB + rotate_left(AA + E + K[i] + input[j], S[i]);
			AA = temp;
		}
		digest[0] += AA;
		digest[1] += BB;
		digest[2] += CC;
		digest[3] += DD;

	}

	// convert from little endian;
	for (int i = 0; i != 4; i++)
		node->digest[i] = __builtin_bswap32(digest[i]);
}