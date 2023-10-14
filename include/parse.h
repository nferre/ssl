#ifndef PARSE_H
# define PARSE_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <stdbool.h>
# include <stdint.h>
# include "math.h"

# define FLAG_P 1
# define FLAG_Q 2
# define FLAG_R 4
# define FLAG_S 8

# define MD5 	1
# define SHA256 2

typedef struct inp {
	void		*data;
	uint64_t	data_length;
	long		total_length;
	uint32_t	*digest;
	struct inp	*next;
} input_t;

typedef struct mode {
	int hash_type;
	int flag;
} info_t;

// parse

void	parse(int argc, char **argv);
void	parse_stdin(void);
void	parse_arg(int argc, char **argv);
void	parse_flags(int argc, char **argv);
void	parse_files(int argc, char **argv, int i);
void	parse_hash_type(int argc, char **argv);

// utils

bool	is_valid_hash_type(char *str);
void	get_file(char *file_name);
input_t	*new_node(long file_size);
void	compute_hash(void);

extern input_t	*begin_g;
extern info_t	info_g;

#endif