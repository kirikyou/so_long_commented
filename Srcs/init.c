/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeulema <jmeulema@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 17:42:28 by jmeulema          #+#    #+#             */
/*   Updated: 2023/03/27 13:37:40 by jmeulema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*The ft_init_next function is part of the game's initialization process.
  It loads several images (textures) from files and assigns them to the appropriate fields in the data structure.
  These images are later used for rendering the game.
  t_data *data: A pointer to the t_data structure that contains the game's state and data.*/
static void	ft_init_next(t_data *data)
{

/*char *relative_path: A string to hold the relative path to the image files.
  int img_width, int img_height: Integers to store the width and height of the loaded images.
  These variables are used to get the dimensions of the images when loading them with MiniLibX functions.*/
	char	*relative_path;
	int		img_width;
	int		img_height;

	relative_path = "./img/Luffy_right.xpm";

/*mlx_xpm_file_to_image is called to load the image file into memory.
  The resulting image is assigned to data->img->player_right.*/
	data->img->player_right = mlx_xpm_file_to_image(data->mlx, relative_path,
			&img_width, &img_height);
	relative_path = "./img/background.xpm";
	data->img->background = mlx_xpm_file_to_image(data->mlx, relative_path,
			&img_width, &img_height);
	relative_path = "./img/exit.xpm";
	data->img->exit = mlx_xpm_file_to_image(data->mlx, relative_path,
			&img_width, &img_height);

/*By loading these images during initialization, the game ensures that all necessary graphical assets
  are ready for rendering when the game starts. This function helps keep the code
  organized by separating the image loading process into a dedicated function.*/
}


/*The ft_init function is responsible for initializing various parts of the game,
  including setting up the map, allocating memory for image data, loading player images,
  and setting initial values for counters.This function ensures that all necessary game data and resources
  are properly initialized before the game starts.*/
void	ft_init(t_data *data, t_map *map)
{
	char	*relative_path;
	int		img_width;
	int		img_height;
	t_img	*img;

/*Initialize Map: Assign the provided map pointer to the map field of the data structure.
Effect: The data structure now has access to the game map.*/
	data->map = map;

/*Allocate Memory for Image Data*/
	img = malloc(sizeof(t_img));

/*If malloc fails, perror prints an error message and exit terminates the program with a failure status.*/
	if (!img)
	{
		perror("Error\nmalloc failed\n");
		exit(EXIT_FAILURE);
	}

/*The allocated memory is assigned to the img pointer, and then to the img field of the data structure.*/
	data->img = img;

/*Load the player's images facing different directions (up, down, left) from the specified files.*/
	relative_path = "./img/Luffy_up.xpm";
	data->img->player_up = mlx_xpm_file_to_image(data->mlx, relative_path,
			&img_width, &img_height);
	relative_path = "./img/Luffy_down.xpm";
	data->img->player_down = mlx_xpm_file_to_image(data->mlx, relative_path,
			&img_width, &img_height);
	relative_path = "./img/Luffy_left.xpm";
	data->img->player_left = mlx_xpm_file_to_image(data->mlx, relative_path,
			&img_width, &img_height);

/*Call the ft_init_next function to load additional images (as previously explained).
  Effect: This ensures that all remaining images needed for the game are loaded.*/
	ft_init_next(data);

/*Initialize Counters:
  Set initial values for the counter and collected fields in the data structure.
  Effect: These fields are used to keep track of game-specific counts, such as steps taken
  or items collected, and are initialized to zero.*/
	data->counter = 0;
	data->collected = 0;
}
