/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeulema <jmeulema@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 14:58:47 by jmeulema          #+#    #+#             */
/*   Updated: 2023/03/27 13:26:44 by jmeulema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	ft_fill_data(t_data *data)
{
	ft_put_background(data);
	ft_create_map(data);
	mlx_hook(data->win, 17, 1L << 2, ft_exit, data);
	mlx_hook(data->win, 2, 0, &ft_basic_commands, data);
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;
	t_map	map;

	ft_window_size(&data, av);
	map.map = ft_calloc(data.size_y + 1, sizeof(char *));
	if (!map.map)
	{
		perror("Error\nCalloc failed\n");
		exit(EXIT_FAILURE);
	}
	ft_init(&data, &map);
	ft_parse_input(&data, av, ac);
	data.mlx = mlx_init();
	if (!data.mlx)
	{
		perror("Error\nInit failed\n");
		exit(EXIT_FAILURE);
	}
	data.win = mlx_new_window(data.mlx, data.size_x, data.size_y, "./so_long");
	ft_fill_data(&data);
	if (check_paths(&data, data.p_y, data.p_x, data.map->collectables) == 0)
		ft_map_error("Error\nInvalid map\n");
	mlx_loop(data.mlx);
	perror("Error\nLoop failed\n");
	exit(EXIT_FAILURE);
}
