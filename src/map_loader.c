/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_loader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 02:26:35 by yben-dje          #+#    #+#             */
/*   Updated: 2026/02/13 20:54:01 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static int	get_obstacle_type(char *data, t_vec2d pos, int width, int height)
{
	if (pos.y == height - 1)
		return (5);
	else if (pos.y == 0)
		return (6);
	else if (pos.x != 0 && pos.x != width - 1 && data[(pos.x - 1) + pos.y
			* width] != '1' && data[(pos.x + 1) + pos.y * width] != '1'
		&& data[(pos.x) + (pos.y - 1) * width] != '1')
		return (1);
	else if (pos.x != 0 && pos.x != width - 1 && data[(pos.x - 1) + pos.y
			* width] != '1' && data[(pos.x + 1) + pos.y * width] == '1')
		return (0);
	else if (pos.x != 0 && pos.x != width - 1 && data[(pos.x - 1) + pos.y
			* width] == '1' && data[(pos.x + 1) + pos.y * width] != '1')
		return (3);
	else if (pos.x != 0 && pos.x != width - 1 && data[(pos.x - 1) + pos.y
			* width] == '1' && data[(pos.x + 1) + pos.y * width] == '1')
		return (2);
	else
		return (4);
}

static int	conv_tile(t_app *app, char *data, t_vec2d pos, t_vec2d size)
{
	if (data[pos.x + pos.y * size.x] == '1')
		return (get_obstacle_type(data, pos, size.x, size.y));
	if (data[pos.x + pos.y * size.x] == 'E')
	{
		app->tile_end_pos = pos;
		return (8);
	}
	if (data[pos.x + pos.y * size.x] == 'C')
	{
		return (-2);
	}
	if (data[pos.x + pos.y * size.x] == 'P')
	{
		app->player.game_start_tile_pos = pos;
		return (-3);
	}
	else if (data[pos.x + pos.y * size.x] == '0')
		;
	else
		error_exit(app, "Unknown tile type in map.");
	return (-1);
}

static int	*get_converted_map_data(t_app *app, t_list *lines, int w, int h)
{
	int		*data;
	int		x;
	int		y;
	char	*map;

	map = list_to_array(lines, ft_memcpy, get_row_len);
	data = malloc(sizeof(int) * w * h);
	if (!data || !map)
	{
		free(map);
		free(data);
		error_exit(app, "Memory allocation in get_converted_map_data");
	}
	y = 0;
	while (y < h)
	{
		x = 0;
		while (x++ < w)
			data[(x - 1) + y * w] = conv_tile(app, map, (t_vec2d){(x - 1), y},
					(t_vec2d){w, h});
		y++;
	}
	free(map);
	return (data);
}

static void	add_line_if_not_null(t_app *app, char *line, t_list *lines)
{
	if (line)
	{
		if (!list_push_back(lines, line))
		{
			free(line);
			list_clear_and_free(lines, free);
			error_exit(app, "Memory allocation error in load_map.");
		}
	}
}

t_map	load_map(t_app *app, const char *path)
{
	int		fd;
	t_list	*lines;
	char	*line;
	t_map	map;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		error_exit(app, "File not found.");
	lines = list_new();
	line = (char *)1;
	while (lines && line)
	{
		line = get_next_line(fd);
		add_line_if_not_null(app, line, lines);
	}
	close(fd);
	if (!lines || lines->size == 0)
		error_exit(app, "Memory allocation error in load_map.");
	check_map_shape(app, lines);
	map.size.x = get_row_len(list_get_at_index(lines, 0));
	map.size.y = lines->size;
	map.data = get_converted_map_data(app, lines, map.size.x, map.size.y);
	player_teleport(app, app->player.game_start_tile_pos);
	list_clear_and_free(lines, free);
	return (map);
}
