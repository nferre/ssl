#include "ssl.h"

void	parse(int argc, char **argv) {
	parse_arg(argc, argv);
	parse_stdin();
}

void	parse_stdin(void)
{
	char buffer[1024];
	size_t bytes_read;
	input_t *node;

	// does not input from stdin too large
	bytes_read = read(STDIN_FILENO, buffer, sizeof(buffer) - 1);
	buffer[bytes_read] = '\0';

	node = new_node(bytes_read);
	node->data = buffer;
}

// check and parse args
void	parse_arg(int argc, char **argv)
{
	parse_hash_type(argc, argv);
	parse_flags(argc, argv);
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

void	parse_flags(int argc, char **argv)
{
	for (int i = 2; i != argc; i++)
	{
		if (argv[i][0] != '-')
		{
			parse_files(argc, argv, i);
			break;
		}
		else
		{
			char f = argv[i][1];
			switch (f)
			{
			case 'p':
				info_g.flag += FLAG_P;
				break;
			case 'q':
				info_g.flag += FLAG_Q;
				break;
			case 'r':
				info_g.flag += FLAG_R;
				break;
			case 's':
				info_g.flag += FLAG_S;
				break;
			default:
				break;
			}
		}
	}
}

void	parse_files(int argc, char **argv, int i)
{
	for(; i != argc; i++)
	{
		if (access(argv[i], F_OK | R_OK) == 0)
			get_file(argv[i]);
		else
			printf("could not calculate hash for file %s (check if file exist/read rights)\n", argv[i]);
	}
}