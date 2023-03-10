/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 20:01:08 by kvebers           #+#    #+#             */
/*   Updated: 2023/03/10 12:32:35 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"    

char	*ft_strjoin2(char *temp, char *buffer, size_t cnt1, size_t cnt2)
{
	char	*new_temp;

	if (temp == NULL)
	{
		temp = malloc(sizeof(char));
		*temp = '\0';
	}
	if (temp == NULL || buffer == NULL)
		return (NULL);
	new_temp = malloc((ft_strlen(buffer) + ft_strlen(temp) + 1) * sizeof(char));
	if (new_temp == NULL)
		return (NULL);
	while (*(temp + cnt1) != '\0')
	{
		*(new_temp + cnt1) = *(temp + cnt1);
		cnt1++;
	}
	while (*(buffer + cnt2) != '\0')
	{
		*(new_temp + cnt1 + cnt2) = *(buffer + cnt2);
		cnt2++;
	}
	*(new_temp + cnt1 + cnt2) = '\0';
	return (free(temp), new_temp);
}

int	is_white_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\n'
		|| c == '\r' || c == '\v' || c == '\f')
		return (ADD);
	return (EXECUTED);
}

int	is_pipe(int c)
{
	if (c == PIPE || c == SHELL_REDIRECTION || c == HERE_DOC
		|| c == FILE_TO_COMMAND || c == COMMAND_TO_FILE)
		return (ADD);
	return (EXECUTED);
}