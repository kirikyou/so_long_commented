/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeulema <jmeulema@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 17:42:28 by jmeulema          #+#    #+#             */
/*   Updated: 2023/03/27 13:35:20 by jmeulema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*The ft_window_size function is responsible for determining the size of the game window
  based on the dimensions of the map file provided as an argument.
  It validates the map file and calculates the window size accordingly.*/
void	ft_window_size(t_data *data, char **av)
{

/*int fd: File descriptor for the map file.
  int len: Length of the map file path string.*/
	int	fd;
	int	len;

/*Get Length of Map File Path:*/
	len = ft_strlen(av[1]);

/*Open Map File:
  If open returns a negative value (fd < 0), it means the file could not be opened.*/
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
	{
		perror("Error\nInvalid map_path/map\n");
		exit(EXIT_FAILURE);
	}

/*Check Map File Extension:
  Validate that the map file has a .ber extension.
  If the conditions are not met, it prints an error message and terminates the program.*/
	if (av[1][len - 4] != '.' || av[1][len - 3] != 'b')
	{
		ft_putstr("Error\nMap has to be .ber\n");
		exit(EXIT_FAILURE);
	}
	if (av[1][len - 2] != 'e' || av[1][len - 1] != 'r')
	{
		ft_putstr("Error\nMap has to be .ber\n");
		exit(EXIT_FAILURE);
	}

/*Calculate Window Size:
  Calculate the width (size_x) and height (size_y) of the game window based on the map dimensions.
  Function Calls:
    ft_line_length(fd): Returns the length of a line in the map file.
    ft_count_lines(fd, data->size_x, IMG_W): Returns the number of lines in the map file.
  Calculations:
    data->size_x: The window width is the line length multiplied by the image width (IMG_W).
    data->size_y: The window height is the number of lines multiplied by the image height (IMG_H).*/
	data->size_x = (ft_line_length(fd) * IMG_W);
	data->size_y = (ft_count_lines(fd, data->size_x, IMG_W) * IMG_H);
}


/*The ft_create_map function is responsible for rendering the game map by placing
  the appropriate game objects(such as the player, walls, collectables, and exit) 
  at their corresponding positions on the map. This function uses the map data to determine
  the placement of each object and calls other functions to draw these objects on the screen.*/
void	ft_create_map(t_data *data)
{
/*Initialize Map Coordinates:*/
	data->map->x = 0;
	data->map->y = 0;

/*Traverse the Map:
  Loop through the map rows. The condition ensures that the loop runs until all rows are processed.
  Calculation: data->size_y / IMG_H gives the total number of rows in the map.*/
	while (data->map->y < (data->size_y / IMG_H))
	{

/*Check and Place Game Objects:
  Check the value at the current map position (data->map->map[data->map->y][data->map->x])
  and place the corresponding game object.*/

/*If the current map position contains 'P', call ft_put_player(data) to place the player.*/
		if (data->map->map[data->map->y][data->map->x] == 'P')
			ft_put_player(data);

/*If it contains '1', call ft_put_objects(data, "./img/wall.xpm") to place a wall.*/
		else if (data->map->map[data->map->y][data->map->x] == '1')
			ft_put_objects(data, "./img/wall.xpm");

/*If it contains 'C', call ft_put_objects(data, "./img/collectables.xpm") to place a collectable.*/
		else if (data->map->map[data->map->y][data->map->x] == 'C')
			ft_put_objects(data, "./img/collectables.xpm");

/*If it contains 'E', call ft_put_objects(data, "./img/exit.xpm") to place the exit.*/
		else if (data->map->map[data->map->y][data->map->x] == 'E')
			ft_put_objects(data, "./img/exit.xpm");

/*Move to the Next Map Position:
  If the current column (x) is less than the total number of columns (data->size_x / IMG_W),
  increment x to move to the next column.*/
		if (data->map->x < (data->size_x / IMG_W))
			data->map->x++;

/*If the current column is the last column, increment y to move to the next row and reset x to 0
  to start from the first column of the new row.*/
		else
		{
			data->map->y++;
			data->map->x = 0;
		}
	}
}
