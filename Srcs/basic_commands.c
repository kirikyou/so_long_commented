/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeulema <jmeulema@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 17:42:28 by jmeulema          #+#    #+#             */
/*   Updated: 2023/03/27 13:27:33 by jmeulema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*It takes a single argument, data, which is a pointer to a t_data structure.
The t_data structure contains information about the game's state,
including the MiniLibX instance (mlx) and the game window (win).*/
int	ft_exit(t_data *data)
{
	/*This line calls the mlx_destroy_window function from the MiniLibX library,
	 which destroys the game window.
	 data->mlx: The MiniLibX instance.
	data->win: The game window to be destroyed.
	This effectively closes the game window and frees associated resources.*/
	mlx_destroy_window(data->mlx, data->win);

	/*This line prints the message "\nYou gave up ! \n" to the standard output.*/
	ft_putstr("\nYou gave up ! \n");

	/*This line calls the exit function
	 from the standard library to terminate the program.
	 EXIT_SUCCESS: A macro defined in stdlib.h that indicates successful program termination.
	 This ensures that the program terminates cleanly and returns a success status to the operating system.*/
	exit(EXIT_SUCCESS);
}


/*This function can be called when the player meets the conditions for winning the game,
 ensuring that they receive appropriate feedback and that the game exits gracefully.*/
void	ft_win(void)
{
	ft_putstr("\nWell done, you finished it\n");
	ft_putstr("You won!\n");
	exit(EXIT_SUCCESS);
}

/*The ft_basic_commands function is designed to handle basic keyboard commands for the game.
  It processes the input command, moves the player accordingly, checks if the player has reached the exit,
  and determines if the player has collected all items to win the game.
  int command: The command received from the keyboard (e.g., a key press).
  t_data *data: A pointer to the t_data structure that contains the game's state and data.*/
int	ft_basic_commands(int command, t_data *data)
{
	if (command == ESC)
		ft_exit(data);

	/*These lines handle the movement commands*/
	else if (command == W)
		ft_move(data, 'y', UP);
	else if (command == S)
		ft_move(data, 'y', DOWN);
	else if (command == A)
		ft_move(data, 'x', LEFT);
	else if (command == D)
		ft_move(data, 'x', RIGHT);

	/*This block checks if the player has reached the exit point ('E') on the map.
	If the player's current position (data->p_y, data->p_x) on the map is an exit ('E').*/
	if (data->map->map[data->p_y][data->p_x] == 'E')
	{
		/*If the number of collected items (data->collected) is equal to the total number 
		of collectables on the map (data->map->collectables), then the player has collected all items.*/
		if (data->collected == data->map->collectables)

		/*If the player has collected all items and reached the exit,
		 the ft_win() function is called to print a congratulatory message and exit the game.*/
			ft_win();
		else

		/*If not all items are collected, the function returns 0.*/
			return (0);
	}
	return (0);
}
