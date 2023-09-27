/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 15:47:27 by ebouvier          #+#    #+#             */
/*   Updated: 2023/09/27 23:19:05 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include "parsing.h"

static void	free_matrice(t_map *map)
{
	int	y;

	y = 0;
	if (!map || !map->map)
		return ;
	while (y < map->y_max)
	{
		free(map->map[y]);
		y++;
	}
	free(map->map);
}

t_bool	is_valid(t_map *map, int x, int y)
{
	t_bool	valid;

	if (x < 0 || x >= map->x_max || y < 0 || y >= map->y_max)
		return (false);
	if (map->map[y][x] == WALL)
		return (false);
	if (map->map[y][x] == EMPTY)
		return (true);
	if (map->map[y][x] == SPACE)
	{
		map->map[y][x] = -1;
		valid = true;
		valid &= is_valid(map, x + 1, y);
		valid &= is_valid(map, x - 1, y);
		valid &= is_valid(map, x, y + 1);
		valid &= is_valid(map, x, y - 1);
		return (valid);
	}
	return (false);
}

t_map_value	**copy_map(t_map *map)
{
	t_map_value	**new_map;
	int			x;
	int			y;

	new_map = malloc(sizeof(t_map_value *) * map->y_max);
	if (!new_map)
		return (NULL);
	y = 0;
	while (y < map->y_max)
	{
		new_map[y] = malloc(sizeof(t_map_value) * map->x_max);
		if (!map->map[y])
		{
			while (y >= 0)
				free(map->map[y--]);
			free(map->map);
			return (NULL);
		}
		x = -1;
		while (++x < map->x_max)
			new_map[y][x] = map->map[y][x];
		y++;
	}
	return (new_map);
}

t_bool	check_closed_map(t_map *map)
{
	int			x;
	int			y;
	t_map		tmp_map;
	t_map_value	**map_copy;

	y = 0;
	map_copy = copy_map(map);
	if (!map_copy)
		return (false);
	tmp_map = (t_map){map_copy, map->x_max, map->y_max, map->data};
	while (y < map->y_max)
	{
		x = 0;
		while (x < map->x_max)
		{
			if (map_copy[y][x] == SPACE && !is_valid(&tmp_map, x, y))
				return (free_matrice(&tmp_map), false);
			x++;
		}
		y++;
	}
	return (free_matrice(&tmp_map), true);
}
