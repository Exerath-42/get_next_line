#include "get_next_line_bonus.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*dest;
	const char	*source;

	dest = dst;
	source = src;
	if ((dest == NULL) && (source == NULL))
		return (NULL);
	while (n)
	{
		*dest = *source;
		dest++;
		source++;
		n--;
	}
	return (dst);
}

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned int	i;

	i = 0;
	while (i < n)
	{
		if (*((unsigned char *)s + i) == (unsigned char)c)
			return ((char *)s + i);
		i++;
	}
	return (NULL);
}

void	ft_bzero(void *s, size_t n)
{
	char	*c;

	c = (char *)s;
	while (n)
	{
		*c = 0;
		c++;
		n--;
	}
}

void	*ft_memrealloc(void *start, size_t old_size, size_t new_size)
{
	void	*ptr;

	ptr = malloc(new_size + 1);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, new_size +1);
	if (old_size <= new_size)
		ptr = ft_memcpy(ptr, start, old_size);
	else if (old_size - new_size > 0)
		ptr = ft_memcpy(ptr, start + (old_size - new_size), new_size);
	free(start);
	return (ptr);
}

size_t	ft_memcat(void **dst, void *src, size_t dst_size, ssize_t src_size)
{
	if (src_size < 0)
		src_size = 0;
	*dst = (char *)ft_memrealloc(*dst, dst_size, dst_size + src_size);
	ft_memcpy(*dst + dst_size, src, src_size);
	return (dst_size + src_size);
}
