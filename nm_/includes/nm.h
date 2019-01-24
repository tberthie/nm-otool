/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 13:38:43 by tberthie          #+#    #+#             */
/*   Updated: 2019/01/24 17:41:44 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NM_H
# define NM_H

# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <ar.h>

# include <sys/mman.h>
# include <sys/stat.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>

# define HEX	"0123456789abcdef"

typedef struct load_command	t_cmd;
typedef struct mach_header			t_header;
typedef struct mach_header_64		t_header_64;
typedef struct symtab_command		t_symtab;
typedef struct segment_command		t_segment;
typedef struct segment_command_64	t_segment_64;
typedef struct section				t_section;
typedef struct section_64			t_section_64;
typedef struct nlist				t_list;
typedef struct nlist_64				t_list_64;
typedef struct ar_hdr				t_arch;

enum			e_sections {
	TEXT = 1, DATA, BSS, COMMON
};

typedef struct	s_symbol {

	const char	*name;
	size_t		value;
	char		symbol;

}				t_symbol;

typedef struct	s_file {

	char		*path;
	int			fd;
	size_t		size;
	char		*data;
	char		arch;
	char		sect[256];
	t_symbol	**symtab;

}				t_file;

void			parse_file(const char *path, char multi);
void			parse_archive(t_file *file);
char			parse_loader(t_file *file);
void			parse_symtab_32(t_symtab *symtab, t_file *file);
void			parse_symtab_64(t_symtab *symtab, t_file *file);
void			print_symbols(t_file *file, char multi);

void			error(const char *format, const char *data);
void			error_exit(const char *format, const char *data);
size_t			get_file_size(int fd);

void			*ft_memalloc(size_t size);
char			ft_strcmp(const char *s1, const char *s2);
char			ft_memcmp(char *d1, char *d2, size_t len);
size_t			ft_strlen(const char *str);
void			ft_memset(char *dst, char c, size_t len);
void			ft_arrpush_ascii(void ***dst, void *elem);
char			*ft_strdup(const char *s1);
void			ft_memcpy(void *dst, const void *src, size_t len);
size_t			ft_atoi(const char *str);
void			ft_strpush(char **dst, char *new);

#endif
