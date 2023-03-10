/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 10:16:14 by jwillert          #+#    #+#             */
/*   Updated: 2023/03/10 14:54:03 by jwillert         ###   ########          */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "minishell.h"

void	debug_print_char_array(char **args)
{
	if (DEBUG)
	{
		printf("Content char array:");
		while (args != NULL && *args != NULL)
		{
			printf(" [%s] ", *args);
			args += 1;
		}
		printf("\n");
	}
}

void	debug_print_t_execute(t_data *data,	t_execute *execute)
{
	int	counter;

	counter = 0;
	if (DEBUG)
	{
		while (counter < data->tokens + 1 && execute[counter].order_str != NULL)
		{
			printf("t_execute: ");
			printf("order_str: [%s] ", execute[counter].order_str);
			printf("order_numb: [%d] ", execute[counter].order_numb);
			printf("full_path: [%s]\n", execute[counter].full_path);
			counter += 1;
		}
	}
}

void	debug_print_t_expander(t_expander *expander)
{
	if (DEBUG)
	{	
		printf("t_expander:\n");
		while (expander != NULL)
		{
			printf("[%s]\n", expander->str);
			expander = expander->next;
		}
	}
}

void	debug_print_t_vector_str(t_vector_str *vector_to_print)
{
	if (DEBUG)
	{
		printf("t_vector:\n");
		printf("str [%s]\n", vector_to_print->str);
		printf("size_used [%zu]\n", vector_to_print->size_used);
		printf("size_allocated [%zu]\n", vector_to_print->size_allocated);
	}
}	