#include "ssl.h"

// global linked list
input_t *begin_g = NULL;
info_t	info_g;

int main(int argc, char **argv)
{
	parse(argc, argv);
	compute_hash();
	//print_nodes();
	//free_nodes();
}