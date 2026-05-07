/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryatan <ryatan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 21:48:36 by ryatan            #+#    #+#             */
/*   Updated: 2026/05/07 21:50:01 by ryatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	fill_arrays(char **split_array, int n, t_int_array *z_array,
		int **colors_row)
{
	int	i;

	i = 0;
	while (i < n)
	{
		z_array->array[i] = ft_atoi(split_array[i]);
		(*colors_row)[i] = parse_color(split_array[i]);
		i++;
	}
	return (1);
}
