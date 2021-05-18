#include "get_next_line.h"

t_list	*create_elem(int fd, t_list **head)
{
	t_list	*elem;

	elem = *head;
	while (elem)
	{
		if (elem->fd == fd)
			return (elem);
		elem = elem->next;
	}
	if (!elem)
	{
		elem = malloc(sizeof(t_list));
		if (!elem)
			return (NULL);
		elem->fd = fd;
		elem->mem = NULL;
		elem->size = 0;
		elem->next = *head;
		*head = elem;
	}
	return (elem);
}

void	ft_freeall(int res, void **buf, int fd, t_list **head)
{
	t_list	*elem;
	t_list	*tmp_elem;

	tmp_elem = NULL;
	if (res <= 0)
	{
		elem = *head;
		while (elem)
		{
			if (elem->fd == fd)
			{
				if (tmp_elem)
					tmp_elem->next = elem->next;
				else
					*head = elem->next;
				free(elem->mem);
				free(elem);
				break ;
			}
			tmp_elem = elem;
			elem = elem->next;
		}
	}
	free(*buf);
}

int	get_line(void **mem, size_t *mem_size, char **line, ssize_t count)
{
	char	*nl;
	size_t	pos;

	pos = 0;
	if (count < 0)
		return (-1);
	nl = ft_memchr(*mem, '\n', *mem_size);
	if (nl)
	{
		pos = nl - (char *)*mem;
		*line = (char *) ft_memrealloc(*line, 0, pos);
		ft_memcpy(*line, *mem, pos);
		*mem = (char *) ft_memrealloc(*mem, *mem_size, *mem_size - pos - 1);
		*mem_size = *mem_size - pos - 1;
		return (1);
	}
	if (!count)
	{
		*line = (char *)ft_memrealloc(*line, 0, *mem_size);
		*line = ft_memcpy(*line, *mem, *mem_size);
		*mem_size = 0;
		return (0);
	}
	return (2);
}

int	get_next_line(int fd, char **line)
{
	static t_list	*head = NULL;
	t_list			*elem;
	void			*buffer;
	ssize_t			count;
	int				res;

	if (fd < 0 || !line || BUFFER_SIZE < 1)
		return (-1);
	buffer = (char *)malloc(BUFFER_SIZE * sizeof(char));
	elem = create_elem(fd, &head);
	if (!buffer || !elem)
		return (-1);
	res = 0;
	*line = NULL;
	while (1)
	{
		count = read(fd, buffer, BUFFER_SIZE);
		elem->size = ft_memcat(&elem->mem, buffer, elem->size, count);
		res = get_line(&elem->mem, &elem->size, line, count);
		if (res != 2)
			break ;
	}
	ft_freeall(res, &buffer, fd, &head);
	return (res);
}
