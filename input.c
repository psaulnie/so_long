/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 11:00:33 by psaulnie          #+#    #+#             */
/*   Updated: 2022/01/03 15:52:56 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	check_exit(t_data data, int key, t_obj	player)
{
	int	as_moved;

	as_moved = 1;
	if (key == KEY_UP && data.current_coin == data.total_coin
		&& data.map.map[player.pos.y - 1][player.pos.x] == 'E')
		data.map.map[player.pos.y - 1][player.pos.x] = 'S';
	else if (key == KEY_LEFT && data.current_coin == data.total_coin
		&& data.map.map[player.pos.y][player.pos.x - 1] == 'E')
		data.map.map[player.pos.y][player.pos.x - 1] = 'S';
	else if (key == KEY_RIGHT && data.current_coin == data.total_coin
		&& data.map.map[player.pos.y][player.pos.x + 1] == 'E')
		data.map.map[player.pos.y][player.pos.x + 1] = 'S';
	else if (key == KEY_DOWN && data.current_coin == data.total_coin
		&& data.map.map[player.pos.y + 1][player.pos.x] == 'E')
		data.map.map[player.pos.y + 1][player.pos.x] = 'S';
	else
		as_moved = 0;
	if (!as_moved)
		return ;
	data.map.map[player.pos.y][player.pos.x] = '0';
	update_map(data.map.map_backup, data.map.map,
		data.map.sprites, data.mlx);
	data.map.map_backup = backup_map(data.map.map);
	mlx_key_hook(data.mlx.mlx_win, anim, &data);
	mlx_loop(data.mlx.mlx);
}

static int	check_input(t_data data, int key, t_obj	player)
{
	if (key == 65307)
		destroy(0, &data);
	if (key == KEY_UP
		&& data.map.map[player.pos.y - 1][player.pos.x] != '1'
		&& data.map.map[player.pos.y - 1][player.pos.x] != 'E')
		return (KEY_UP);
	else if (key == KEY_LEFT
		&& data.map.map[player.pos.y][player.pos.x - 1] != '1'
		&& data.map.map[player.pos.y][player.pos.x - 1] != 'E')
		return (KEY_LEFT);
	else if (key == KEY_RIGHT
		&& data.map.map[player.pos.y][player.pos.x + 1] != '1'
		&& data.map.map[player.pos.y][player.pos.x + 1] != 'E')
		return (KEY_RIGHT);
	else if (key == KEY_DOWN
		&& data.map.map[player.pos.y + 1][player.pos.x] != '1'
		&& data.map.map[player.pos.y + 1][player.pos.x] != 'E')
		return (KEY_DOWN);
	else
		check_exit(data, key, player);
	return (0);
}

int	input(int key, t_data *data)
{
	t_obj	player;
	int		as_moved;

	as_moved = 1;
	get_player_pos(&player, data->map.map);
	if (check_input(*data, key, player) == KEY_UP)
		data->map.map[player.pos.y - 1][player.pos.x] = 'P';
	else if (check_input(*data, key, player) == KEY_LEFT)
		data->map.map[player.pos.y][player.pos.x - 1] = 'P';
	else if (check_input(*data, key, player) == KEY_RIGHT)
		data->map.map[player.pos.y][player.pos.x + 1] = 'P';
	else if (check_input(*data, key, player) == KEY_DOWN)
		data->map.map[player.pos.y + 1][player.pos.x] = 'P';
	else
		as_moved = 0;
	if (check_input(*data, key, player) != 0)
		data->map.map[player.pos.y][player.pos.x] = '0';
	get_player_pos(&player, data->map.map);
	if (data->map.map_backup[player.pos.y][player.pos.x] == 'C')
		data->current_coin++;
	if (!as_moved)
		return (0);
	printf("%d\n", data->movement++);
	enemy(data);
	update_map(data->map.map_backup, data->map.map,
		data->map.sprites, data->mlx);
	data->map.map_backup = backup_map(data->map.map);
	return (0);
}
