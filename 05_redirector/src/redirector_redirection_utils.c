/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirector_redirection_utils.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 11:11:34 by jwillert          #+#    #+#             */
/*   Updated: 2023/04/12 19:09:33 by jwillert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"		// needed for t_data, MACROS
#include "libft.h"			// needed for ft_split()
#include <stdlib.h>			// needed for free()

char	*redirector_get_filename(t_data *data, int index)
{
	char	**split_array;
	char	*str_filename;

	split_array = ft_split(data->combine[index].combined_str, ' ');
	if (split_array == NULL)
		return (NULL);
	str_filename = split_array[1];
	free(split_array[0]);
	free(split_array);
	return (str_filename);
}

int	redirector_find_end_of_command(t_data *data, int index)
{
	while (index < data->commands_to_process
		&& data->combine[index].combined_str != NULL)
	{
		if (data->combine[index].command->order_numb == PIPE
			|| data->combine[index].command->order_numb == LAST_PIPE)
		{
			break ;
		}
		index += 1;
	}
	return (index);
}