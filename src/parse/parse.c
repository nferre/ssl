#include "ssl.h"

void	parse(int argc, char **argv) {
	parse_hash_type(argc, argv);

	parse_files(argc, argv);

	if (!isatty(STDIN_FILENO) || argc == 2) // only if file descriptor is not from terminal (accept pipes and redirections) or no file provided
		parse_stdin();
}

#define BLOCK_SIZE 100
void	parse_stdin(void)
{
	char 	buffer[BLOCK_SIZE];
	char	*temp_data = malloc(BLOCK_SIZE);
	size_t	bytes_read = 0;
	input_t *node;
	size_t	total_bytes = 0;
	size_t	size_data = 100;


	// read what we can
	while ((bytes_read = fread(buffer, sizeof(char), BLOCK_SIZE, stdin)) > 0)
	{
		// do we need to realloc ?
		if (total_bytes + bytes_read > size_data)
		{
			size_data += BLOCK_SIZE;
			temp_data = (char *)realloc(temp_data, size_data);
		}

		// copy what we read to a tmp buffer
		memcpy(temp_data + total_bytes, buffer, bytes_read);
		total_bytes += bytes_read;
	}

	//new node and transfer data
	node = new_node(total_bytes, "stdin");
	memcpy(node->data, temp_data, total_bytes);

	free(temp_data);
}

// is_valid_hash_type sets info_g.hash_type
void	parse_hash_type(int argc, char **argv)
{
	if (argc == 1 || !is_valid_hash_type(argv[1]))
	{
		puts("invalid args");
		exit(1);
	}
}

void	parse_files(int argc, char **argv)
{
	for(int i = 2; i != argc; i++)
	{
		if (access(argv[i], F_OK | R_OK) == 0)
			get_file(argv[i]);
		else
			printf("could not calculate hash for file %s (check if file exist/read rights)\n", argv[i]);
	}
}