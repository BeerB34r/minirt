/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   ft_calloc.c                                         :+:    :+:           */
/*                                                      +:+                   */
/*   By: mde-beer <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/10/08 18:53:53 by mde-beer       #+#    #+#                */
/*   Updated: 2024/10/14 14:32:22 by mde-beer       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <stdint.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ret;
	size_t	memsize;

	if (!nmemb || !size)
		return (NULL);
	if ((SIZE_MAX / nmemb) < size)
		return (NULL);
	memsize = nmemb * size;
	ret = malloc(memsize);
	if (!ret)
		return (NULL);
	ft_memset(ret, 0, (memsize));
	return (ret);
}
