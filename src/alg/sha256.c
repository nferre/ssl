#include "ssl.h"

uint32_t K1[] = { 0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 
0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 
0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 
0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 
0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 
0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 
0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 
0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 
0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2 };

void	sha256(input_t *node)
{
	//padding
	for (uint64_t i = 0; i < (node->total_length - (node->data_length + 8 % 64)); i++)
		*(uint8_t*)(node->data + node->data_length + i) = (i == 0) ? 128 : 0;

	// add length end of block in big endian
	*(uint32_t *)(node->data + node->total_length - 4) = __builtin_bswap32((uint32_t)(node->data_length * 8));
	*(uint32_t *)(node->data + node->total_length - 8) = __builtin_bswap32((uint32_t)((node->data_length * 8) >> 32));

	compute_sha256(node);
}

void	compute_sha256(input_t *node)
{
	uint32_t digest[8] = {H0, H1, H2, H3, H4, H5, H6, H7};

	for (int block = 0; block < node->total_length; block += 64) // for each block (512 bits)
	{
		uint32_t input[64];
		uint32_t s0, s1;

		// 64 byte block to 16x(32 bits blocks)
		for (int i = 0; i < 16; i++)
			input[i] = __builtin_bswap32(*(uint32_t *)(node->data + block + i * 4));

		for (int i = 16; i < 64; i++)
		{
			s0 = ROTR(input[i - 15], 7) ^ ROTR(input[i - 15], 18) ^ (input[i - 15] >> 3);
			s1 = ROTR(input[i - 2], 17) ^ ROTR(input[i - 2], 19) ^ (input[i - 2] >> 10);
			input[i] = input[i - 16] + s0 + input[i - 7] + s1;
		}

		uint32_t a = digest[0];
		uint32_t b = digest[1];
		uint32_t c = digest[2];
		uint32_t d = digest[3];
		uint32_t e = digest[4];
		uint32_t f = digest[5];
		uint32_t g = digest[6];
		uint32_t h = digest[7];

		for(int i = 0; i < 64; i++)
		{
			s1 = ROTR(e, 6) ^ ROTR(e, 11) ^ ROTR(e, 25);
			uint32_t ch = (e & f) ^ ((~e) & g);
			uint32_t temp1 = h + s1 + ch + K1[i] + input[i];
			s0 = ROTR(a, 2) ^ ROTR(a, 13) ^ ROTR(a, 22);
			uint32_t maj = (a & b) ^ (a & c) ^ (b & c);
			uint32_t temp2 = s0 + maj;

			h = g;
			g = f;
			f = e;
			e = d + temp1;
			d = c;
			c = b;
			b = a;
			a = temp1 + temp2;
		}

		digest[0] += a;
		digest[1] += b;
		digest[2] += c;
		digest[3] += d;
		digest[4] += e;
		digest[5] += f;
		digest[6] += g;
		digest[7] += h;
	}
	for (int i = 0; i != 8; i++)
		node->digest[i] = digest[i];
}