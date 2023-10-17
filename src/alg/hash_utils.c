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
			case SHA256:
				sha256(tmp);
				break;
		}
	}
}

void	print_nodes()
{
	for (input_t *node = begin_g; node != NULL; node = node->next)
	{
		printf("%s - (%s)\t ", info_g.hash_name, node->file_name);
		for (int i = 0; i != (info_g.hash_type == MD5 ? 4 : 8); i++)
			printf("%08x", node->digest[i]);
		puts("");
	}
}

void	free_nodes()
{
	input_t *node = begin_g;

	for (input_t *tmp = NULL; node != NULL;)
	{
		tmp = node;
		node = node->next;
		free(tmp->data);
		free(tmp->digest);
		free(tmp);
	}
	begin_g = NULL;
	free(info_g.hash_name);
}
