/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeulema <jmeulema@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 17:42:28 by jmeulema          #+#    #+#             */
/*   Updated: 2023/03/27 13:26:09 by jmeulema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*The ft_map_error function is designed to handle errors related to the game's map.
When an error is encountered, this function will print an error message and terminate the program.
*/
void	ft_map_error(char *error_msg)
{
	ft_putstr(error_msg);

/*Terminates the program with a failure status.*/
	exit(EXIT_FAILURE);
}


/*The ft_check_walls function is designed to validate the structure and content of the game map.
  It ensures that the map meets specific requirements:

    The map must be rectangular.
    The map must only contain valid characters.
    The map must be surrounded by walls.*/
static void	ft_check_walls(t_data *data)
{
	int	x;
	int	y;

	y = 0;

/*Loop Through Each Row of the Map*/
	while (y < (data->size_y / IMG_H))
	{

	/*Checks if the length of the current row (ft_strlen(data->map->map[y])) matches the expected width
	  (data->size_x / IMG_W). If not, it raises an error indicating that the map must be rectangular.*/
		if ((int)ft_strlen(data->map->map[y]) != data->size_x / IMG_W)
			ft_map_error("Error\nMap has to be rectangular\n");

/*nitialize x (Column Index) and Loop Through Each Column of the Current Row*/
		x = 0;
		while (x < (data->size_x / IMG_W))
		{

/*Check for Valid Characters in the Map*/
			if (data->map->map[y][x] != '0' && data->map->map[y][x] != '1' &&
				data->map->map[y][x] != 'C' && data->map->map[y][x] != 'P' &&
				data->map->map[y][x] != 'E')
				ft_map_error("Error\nShould contained '0','1','C','P','E'\n");

/*Check if the Map is Surrounded by Walls (First and Last Rows/Columns)*/
			else if ((y == 0 || x == 0) && data->map->map[y][x] != '1')
				ft_map_error("Error\nMap has to be surrounded by walls\n");
			else if ((y == (data->size_y / IMG_H - 1)
					|| x == (data->size_x / IMG_W - 1))
				&& data->map->map[y][x] != '1')
				ft_map_error("Error\nMap has to be surrounded by walls\n");
/*Moves to the next column in the current row.*/
			x++;
		}
/*Moves to the next row of the map after all columns of the current row have been checked.*/
		y++;
	}
}

static void	ft_check_content(t_data *data)
{
	int	y;
	int	exit;
	int	player;

	exit = 0;
	player = 0;

/*to count the number of collectables in the map.*/
	data->map->collectables = 0;
	y = 0;

/*Iterates through each row of the map. The loop continues as long as the map and the current row exist.*/
	while (data->map->map && data->map->map[y])
	{

/*Uses the ft_count_c function to count the occurrences of 'E' (exits), 'P' (players), and 'C' (collectables) in the current row.
Increment exit, player, and data->map->collectables: Adds the counts to the respective variables.
Increment y: Moves to the next row.*/
		exit += ft_count_c(data->map->map[y], 'E');
		player += ft_count_c(data->map->map[y], 'P');
		data->map->collectables += ft_count_c(data->map->map[y], 'C');
		y++;
	}
	if (player != 1)
		ft_map_error("Error\nOnly valid map if one player is contained\n");
	if (exit != 1)
		ft_map_error("Error\nOnly valid map if one exit is contained\n");
	if (data->map->collectables == 0)
		ft_map_error("Error\nOnly valid map if at least 1 fruit is contained\n");
}

/*it checks that exactly one additional argument (the map file path) is passed when running the program*/
static void	ft_input_error(int ac)
{
	if (ac != 2)
	{
		ft_map_error("Error\nUsage './so_long mappath/mapname.ber\n");
		exit(EXIT_FAILURE);
	}
}

void	ft_parse_input(t_data *data, char **av, int ac)
{
	int		fd;
	int		i;
	int		bytes;
	char	buffer[2];

	ft_input_error(ac);
	i = 0;
	bytes = 1;
	buffer[1] = '\0';
	fd = open(av[1], O_RDONLY);

/*Reads the map file character by character and constructs the 2D map array:

    While Loop: Continues reading as long as bytes == 1 (i.e., one character is successfully read).
    Read Character: Reads one character from the file into buffer.
    Break on EOF: If bytes != 1, break the loop (end of file reached).
    Append Character: If the character is not a newline (\n) or null terminator (\0), append it to the current line in the map array using ft_strjoin.
    New Line: If the character is a newline, move to the next line in the map array by incrementing i.*/
	while (bytes == 1)
	{
		bytes = read(fd, buffer, 1);
		if (bytes != 1)
			break ;
		if (buffer[0] != '\n' && buffer[0] != '\0')
		{
			data->map->map[i] = ft_strjoin(data->map->map[i], buffer);
		}
		else
			i++;
	}

/*Calls the ft_check_content function to validate the map's content,
  ensuring it has the correct number of players, exits, and collectables.*/
	ft_check_content(data);

/*Calls the ft_check_walls function to ensure the map is properly surrounded by walls
  and meets the required rectangular shape and valid character conditions.*/
	ft_check_walls(data);
}
