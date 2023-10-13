#include "ssl.h"

void	compute_hash(void)
{
	for (input_t *tmp = begin_g; tmp != NULL; tmp = tmp->next)
	{
		switch (info_g.hash_type)
		{
			case MD5:
				md5(tmp);
				break;
		}
	}
}

