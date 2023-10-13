#include "ssl.h"

// modify to have functions pointers of all alg
bool	is_valid_hash_type(char *hash_type)
{
	if (strcmp("md5", hash_type) == 0)
	{
		info_g.hash_type = MD5;
		return true;
	}
	else if (strcmp("sha256", hash_type) == 0)
	{
		info_g.hash_type = SHA256;
		return true;
	}
	
	return false;
}

void	get_file(char *file_name)
{
	input_t *node;
	FILE *f = fopen(file_name, "r");

	if (f == NULL)
		{ printf("Error while opening the file %s\n", file_name); exit(1); }


	//get file size
	fseek(f, 0, SEEK_END);
	size_t file_size = ftell(f);
	fseek(f, 0, SEEK_SET);
	
	node = new_node(file_size); // create new node

	// get file content
	size_t bytes_read = fread(node->data, 1, file_size, f);
	fclose(f);
	if (bytes_read != file_size) 
		{ printf("Error while reading the file %s\n", file_name); exit(1); }
}

input_t	*new_node(long file_size)
{
	input_t *tmp = begin_g;
	input_t *new = malloc(sizeof(input_t));
	
	if (new == NULL)
		{ puts("could not allocate"); exit(1); }

	if (tmp == NULL)
		begin_g = new;
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
	
	new->total_length = file_size + 4 + (64 - ((file_size + 4) % 64));
	new->data = malloc(new->total_length); // malloc for data (file_size) + padding (512 - (file_size + 64 % 512)) + length (64 bits = 4 bytes)
	new->digest = malloc(MD5_LENGTH);
	new->data_length = (uint64_t)file_size;
	new->next = NULL;

	return new;
}