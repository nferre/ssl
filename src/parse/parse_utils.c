#include "ssl.h"

bool	is_valid_hash_type(char *hash_type)
{
	if (strcmp("md5", hash_type) == 0)
	{
		info_g.hash_type = MD5;
		info_g.hash_name = strdup("md5");
		return true;
	}
	else if (strcmp("sha256", hash_type) == 0)
	{
		info_g.hash_type = SHA256;
		info_g.hash_name = strdup("sha256");
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
	
	node = new_node(file_size, file_name); // create new node

	// get file content
	size_t bytes_read = fread(node->data, 1, file_size, f);
	fclose(f);
	if (bytes_read != file_size) 
		{ printf("Error while reading the file %s\n", file_name); exit(1); }
}

input_t	*new_node(long file_size, char *file_name)
{
	input_t *tmp = begin_g;
	input_t *new = malloc(sizeof(input_t));
	
	if (new == NULL)
		{ puts("could not allocate"); exit(1); }

	new->total_length = file_size + 8 + (64 - ((file_size + 8) % 64));
	new->data = malloc(new->total_length); // malloc for data (file_size) + padding (64 - (file_size + 8 % 64)) + length (64 bits = 8 bytes)
	new->digest = malloc(info_g.hash_type == MD5 ? MD5_LENGTH : SHA256_LENGTH);
	new->data_length = (uint64_t)file_size;
	new->file_name = file_name;
	new->next = NULL;
	
	if (tmp == NULL)
		begin_g = new;
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
	return new;
}