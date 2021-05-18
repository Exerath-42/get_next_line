#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

typedef struct s_list
{
	int				fd;
	void			*mem;
	size_t			size;
	struct s_list	*next;
}					t_list;

int		get_next_line(int fd, char **line);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
void	ft_bzero(void *s, size_t n);
void	*ft_memrealloc(void *start, size_t old_size, size_t new_size);
size_t	ft_memcat(void **dst, void *src, size_t dst_size, ssize_t src_size);

#endif