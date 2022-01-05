/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 11:28:44 by psaulnie          #+#    #+#             */
/*   Updated: 2022/01/05 10:18:25 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int	destroy_mouse(t_data *data)
{
	if (data->map.map)
		free_tab(data->map.map);
	if (data->map.map_backup)
		free_tab(data->map.map_backup);
	if (data->mlx.mlx)
	{
		mlx_clear_window(data->mlx.mlx, data->mlx.mlx_win);
		mlx_destroy_window(data->mlx.mlx, data->mlx.mlx_win);
	}
	exit(1);
}

int	destroy(int key, t_data *data)
{
	if (!key)
		exit (1);
	if (data->map.map)
		free_tab(data->map.map);
	if (data->map.map_backup)
		free_tab(data->map.map_backup);
	if (data->mlx.mlx)
	{
		mlx_clear_window(data->mlx.mlx, data->mlx.mlx_win);
		mlx_destroy_window(data->mlx.mlx, data->mlx.mlx_win);
	}
	free_tab(data->map.sprites);
	exit(1);
}
