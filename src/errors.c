/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryatan <ryatan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 09:33:11 by ryatan            #+#    #+#             */
/*   Updated: 2026/05/08 10:01:32 by ryatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	print_error(int err)
{
	if (err == WRONG_ARGS)
		write(2, "Wrong argument count.\n", 22);
	else if (err == WRONG_MAP_FORMAT)
		write(2, "Map has a wrong format.\n", 25);
	else if (err == NO_FILE)
		write(2, "File not found.\n", 16);
	else if (err == NO_PERMISSIONS)
		write(2, "No permissions to access this file.\n", 36);
}

int	error_checks(int argc, char **argv)
{
	if (argc != 2)
		return (print_error(WRONG_ARGS), 1);
	if (access(argv[1], F_OK) < 0)
		return (print_error(NO_FILE), 1);
	if (access(argv[1], R_OK) < 0)
		return (print_error(NO_PERMISSIONS), 1);
	return (0);
}
