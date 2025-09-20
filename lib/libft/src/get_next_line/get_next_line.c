/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   get_next_line.c                                     :+:    :+:           */
/*                                                      +:+                   */
/*   By: mde-beer <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/10/18 10:21:19 by mde-beer       #+#    #+#                */
/*   Updated: 2024/10/18 14:04:10 by mde-beer       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>

int	is_line(const char *str)
{
	while (*str)
		if (*str++ == '\n')
			return (1);
	return (0);
}

void	*free_if_exists(void *ptr)
{
	if (ptr)
		free(ptr);
	return (NULL);
}

int	do_read(t_buffer *const buf)
{
	int	buf_len;

	if (buf->index >= buf->size)
	{
		buf->size = read(buf->key, buf->buf, BUFFER_SIZE);
		buf->index = 0;
	}
	if (buf->size < 1)
		return (0);
	buf_len = 0;
	while (buf->index + buf_len < buf->size)
		if (buf->buf[buf->index + buf_len++] == '\n')
			return (buf_len);
	return (buf_len);
}

int	build_line(t_buffer *const buf, char **ret)
{
	const int	slen = gnl_strlen(*ret);
	const int	blen = do_read(buf);
	char *const	out = malloc(sizeof(char) * (slen + blen + 1));
	int			i;

	if (blen < 1)
	{
		free_if_exists(out);
		return (buf->size);
	}
	if (!out)
		return (-1);
	i = -1;
	while (++i < slen)
		out[i] = (*ret)[i];
	while (i - slen < blen)
		out[i++] = buf->buf[buf->index++];
	out[i] = 0;
	free_if_exists(*ret);
	*ret = out;
	if (is_line(*ret))
		return (0);
	return (1);
}

char	*get_next_line(int fd)
{
	static t_buffer	buf = {.key = 0, .size = 0, .index = 0};
	char			*ret;
	int				rval;

	buf.key = fd;
	ret = NULL;
	rval = 1;
	while (rval == 1)
		rval = build_line(&buf, &ret);
	if (rval == -1)
		return (free_if_exists(ret));
	return (ret);
}
