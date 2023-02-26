/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 17:11:31 by kvebers           #+#    #+#             */
/*   Updated: 2023/02/26 10:24:51 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	argument_protection(t_data *data, int argc, char **argv, char **envp)
{
	if (argc > 1)
		return (Error);
	put_to_linked_list_expander(data, envp);
	data->argv = argv;
	return (Executed);
}
