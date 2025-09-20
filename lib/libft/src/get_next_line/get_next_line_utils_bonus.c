/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   get_next_line_utils_bonus.c                         :+:    :+:           */
/*                                                      +:+                   */
/*   By: mde-beer <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/10/18 14:03:40 by mde-beer       #+#    #+#                */
/*   Updated: 2024/11/04 14:44:45 by mde-beer       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include <get_next_line_bonus.h>
#include <stdlib.h>

int	gnl_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

t_buffer	*get_buf(t_buffer **head, int key)
{
	t_buffer	*ret;

	if (!*head)
	{
		*head = get_new(key);
		return (*head);
	}
	ret = *head;
	while (ret)
	{
		if (ret->key == key)
			return (ret);
		if (!ret->next)
			break ;
		ret = ret->next;
	}
	ret->next = get_new(key);
	return (ret->next);
}

t_buffer	*get_new(int key)
{
	t_buffer	*ret;

	ret = (t_buffer *)malloc(sizeof(t_buffer));
	if (!ret)
		return (NULL);
	ret->key = key;
	ret->size = 0;
	ret->index = 0;
	ret->next = NULL;
	return (ret);
}

void	free_buffer(t_buffer **head, int key)
{
	t_buffer	*current;
	t_buffer	*next;

	if (!*head)
		return ;
	current = *head;
	next = current->next;
	if (current->key == key)
	{
		free(current);
		*head = next;
		return ;
	}
	while (next)
	{
		if (next->key == key)
		{
			current->next = next->next;
			free(next);
			return ;
		}
		current = next;
		next = current->next;
	}
}
