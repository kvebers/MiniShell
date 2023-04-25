/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 10:50:57 by kvebers           #+#    #+#             */
/*   Updated: 2023/04/25 07:34:28 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"	// needed for t_data
#include <stdio.h>		// needed for printf(), perror()
#include "libft.h"		// needed for ft_split(), ft_strlen(), ft_strncmp()
#include "libme.h"		// needed for free_char_array()
#include <unistd.h>		// needed for chdir(), access(), getcwd()

// argument parsing cd bla bla
// no such file or directory
// update oldpwd
// update pwd
// home
// some_path	| by name directory
// -			| previous directory    // @todo double --
// ..			| parent directory
// .			| current directory
// ~			| home directory    // @todo @error no such access right now
// /			| root directory i think

static char	*get_var_content(char **envp, char *var_name)
{
	int	var_name_length;

	var_name_length = ft_strlen(var_name);
	while (envp != NULL && *envp != NULL)
	{
		if (ft_strncmp(var_name, *envp, var_name_length) == 0)
		{
			if (*(*envp + var_name_length) != '\0')
			{
				return (*envp + var_name_length);
			}
		}
	envp += 1;
	}
	return (NULL);
}

static int	find_var_index(char **envp, char *var_name)
{
	int	index;
	int	var_name_length;

	var_name_length = ft_strlen(var_name);
	index = 0;
	while (envp != NULL && envp[index] != NULL)
	{
		if (ft_strncmp(var_name, envp[index], var_name_length) == 0)
		{
			return (index);
		}
		index += 1;
	}
	return (0);
}

static int	update_envp(t_data *data)
{
	int	index_oldpwd;
	int	index_pwd;

	index_oldpwd = find_var_index(data->envp, "OLDPWD=");
	index_pwd = find_var_index(data->envp, "PWD=");
	free(data->envp[index_oldpwd]);
	data->envp[index_oldpwd] = ft_strjoin("OLD", data->envp[index_pwd]);
	if (data->envp[index_oldpwd] == NULL)
	{
		return (ERROR);
	}
	free(data->envp[index_pwd]);
	data->envp[index_pwd] = ft_strjoin("PWD=", getcwd(NULL, 0));
	if (data->envp[index_pwd] == NULL)
	{
		return (ERROR);
	}
	return (EXECUTED);
}

int	builtin_cd(t_data *data, int index)
{
	char	**input;
	char	*temp;
	
	input = ft_split(data->combine[index].combined_str, ' ');
	if (input == NULL)
	{
		data->exit_status = 1;
		return (ERROR);
	}
	temp = NULL;
	if (input[1] == NULL)
	{
		temp = get_var_content(data->envp, "HOME=");
	}
	else if (ft_strncmp("-", input[1], 1) == 0)
	{
		temp = get_var_content(data->envp, "OLDPWD=");
		if (temp == NULL)
		{
			data->exit_status = 1;
			ft_putstr_fd("cd: OLDPWD not set\n", 2);
		}
	}
	else
		temp = input[1];
	if (temp != NULL)
	{
		if (access(temp, F_OK) == -1)
			perror("access");
		if (chdir(temp) == 1)
			perror("chdir");
	}
	if (update_envp(data) == ERROR)
	{
		data->exit_status = 1;
		return (ERROR);
	}
	free_char_array(input);
	return (EXECUTED);
}
