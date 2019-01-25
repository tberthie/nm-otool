/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 19:54:46 by tberthie          #+#    #+#             */
/*   Updated: 2019/01/25 16:11:33 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
  
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

enum				e_sect
{
	TEXT, DATA, BSS, COMMON
};

typedef struct		s_file
{
	char			lib;

	char			*path;
	char			format;
	
	void			*data;
	size_t			size;

	void			*payload;

}					t_file;

typedef struct		s_lib
{
	char			lib;

	char			*path;

	t_file			**objs;

}					t_lib;

void				*get_file_data(const char *path);
t_file				*load_file(const char *path, void *data, size_t size);
t_lib				*load_lib(const char *path, void *data, size_t size);

size_t				ft_strlen(const char *str);
void				ft_parrpush(void ***tab, void *elem);
void				*ft_memalloc(size_t bytes);
char				*ft_strdup(const char *str);
void				ft_memcpy(void *dst, const void *src, size_t len);
size_t				ft_atoi(const char *str);
int					ft_memcmp(void *s1, void *s2, size_t len);
int					ft_strcmp(const char *s1, const char *s2);
void				ft_memset(void *dst, char c, size_t len);

void				error(const char *format, const char *data);
void				error_exit(const char *format, const char *data);
size_t				get_file_size(int fd);
