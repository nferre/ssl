#include "ssl.h"

void	parse(int argc, char **argv) {
	parse_hash_type(argc, argv);

	parse_files(argc, argv);

	if (!isatty(STDIN_FILENO) || argc == 2) // only if file descriptor is not from terminal (accept pipes and redirections) or no file provided
		parse_stdin();
}

void	parse_stdin(void)
{
	char *buffer = malloc(1024);
	size_t bytes_read;
	input_t *node;

	// does not work with input from stdin too large
	bytes_read = fread(buffer, sizeof(char), sizeof(buffer), stdin);
	buffer[bytes_read] = '\0';

	node = new_node(bytes_read, "stdin");
	memcpy(node->data, buffer, bytes_read);
	free(buffer);
}

// is_valid_hash_type sets info_g.hash_type
void	parse_hash_type(int argc, char **argv)
{
	if (argc == 1 || !is_valid_hash_type(argv[1]))
	{
		puts("invalid args");
		exit(0); //change me to 1
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