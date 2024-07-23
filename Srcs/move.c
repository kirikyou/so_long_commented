/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeulema <jmeulema@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 17:42:28 by jmeulema          #+#    #+#             */
/*   Updated: 2023/03/27 13:24:26 by jmeulema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*The ft_player_move function is responsible for updating the player's position
  on the screen in response to movement commands. It uses the MiniLibX library to draw
  the player's image at the new position based on the direction of movement.
  t_data *data: A pointer to the t_data structure that contains the game's state and data.
  char position: Indicates whether the movement is vertical ('y') or horizontal ('x').
  int direction: Indicates the direction of movement (UP, DOWN, LEFT, RIGHT).*/
static void	ft_player_move(t_data *data, char position, int direction)
{
	/*Move Up:
	Checks if the movement is vertical (position == 'y') and in the upward direction (direction == UP).*/
	if (position == 'y' && direction == UP)
	{
/*Calls mlx_put_image_to_window to draw the player's image facing up at the new position.
    data->mlx: The MiniLibX instance.
    data->win: The game window.
    data->img->player_up: The player's image facing up.
    (data->p_x * IMG_W): The x-coordinate of the new position.
    (data->p_y * IMG_H): The y-coordinate of the new position.*/
		mlx_put_image_to_window(data->mlx, data->win, data->img->player_up,
			(data->p_x * IMG_W), (data->p_y * IMG_H));
	}
	if (position == 'y' && direction == DOWN)
	{
		mlx_put_image_to_window(data->mlx, data->win, data->img->player_down,
			(data->p_x * IMG_W), (data->p_y * IMG_H));
	}

/*Move Left:
  Checks if the movement is horizontal (position == 'x') and in the leftward direction (direction == LEFT).*/
	if (position == 'x' && direction == LEFT)
	{

/*Calls mlx_put_image_to_window to draw the player's image facing left at the new position.
  data->img->player_left: The player's image facing left.*/
		mlx_put_image_to_window(data->mlx, data->win, data->img->player_left,
			(data->p_x * IMG_W), (data->p_y * IMG_H));
	}
	if (position == 'x' && direction == RIGHT)
	{
		mlx_put_image_to_window(data->mlx, data->win, data->img->player_right,
			(data->p_x * IMG_W), (data->p_y * IMG_H));
	}
}


/*The ft_collect function is responsible for handling the collection of items (collectables) in the game.
  When the player moves over a collectable, this function increments the collected item count,
  updates the map, and refreshes the player's position on the screen.*/
static void	ft_collect(t_data *data, char pos, int dir)
{
/*Increment Collected Item Count*/
	data->collected++;

/*Update the map data to reflect that the collectable at the player's current position has been collected.
Changes the map character at the player's position (data->p_y, data->p_x) to '0', indicating an empty space.*/
	data->map->map[data->p_y][data->p_x] = '0';

/*Redraw the background image at the player's current position to cover up the collected item.*/
	mlx_put_image_to_window(data->mlx, data->win, data->img->background,
		(data->p_x * IMG_W), (data->p_y * IMG_H));

/*Call the ft_player_move function to redraw the player's image at the new position.*/
	ft_player_move(data, pos, dir);
}

/*The ft_do_move function handles the player's movement in the game.
  It updates the player's position on the map and refreshes the game window accordingly,
  ensuring that the player does not move into walls ('1').*/
static void	ft_do_move(t_data *data, char pos, int dir)
{

/*Checks if the movement is vertical (pos == 'y') and if the next position in the y-direction is not a wall
  (data->map->map[data->p_y + 1 * dir][data->p_x] != '1').
If the condition is true, the player can move vertically.*/
	if (pos == 'y' && data->map->map[data->p_y + 1 * dir][data->p_x] != '1')
	{

/*Checks if the player's current position is an exit ('E').
  If true, redraw the exit image at the player's current position before moving,
  to maintain the correct visual state of the exit on the map.*/
		if (data->map->map[data->p_y][data->p_x] == 'E')
			mlx_put_image_to_window(data->mlx, data->win, data->img->exit,
				(data->p_x * IMG_W), (data->p_y * IMG_H));

/*Update the player's y-coordinate to the new position in the specified direction.*/
		data->p_y = data->p_y + 1 * dir;
	}

/*Checks if the movement is horizontal (pos == 'x') and if the next position in the x-direction is not a wall
  (data->map->map[data->p_y][data->p_x + 1 * dir] != '1').
  If the condition is true, the player can move horizontally.*/
	else if (pos == 'x' && data->map->map[data->p_y][data->p_x + 1 * dir]
		!= '1')
	{
/*Checks if the player's current position is an exit ('E').
  If true, redraw the exit image at the player's current position before moving,
  to maintain the correct visual state of the exit on the map.*/
		if (data->map->map[data->p_y][data->p_x] == 'E')
			mlx_put_image_to_window(data->mlx, data->win, data->img->exit,
				(data->p_x * IMG_W), (data->p_y * IMG_H));

/*Update the player's x-coordinate to the new position in the specified direction.*/
		data->p_x = data->p_x + 1 * dir;
	}
}


/*The ft_do_exit_move function checks whether the player is trying to exit the game area without
  collecting all required items (e.g., devil's fruits). If the player tries to exit without collecting all items,
   it displays a message instructing the player to collect all items before leaving.*/
static void	ft_do_exit_move(t_data *data, char pos)
{

/*Checks if the movement is vertical (pos == 'y'), if the player's current position is an exit
  (data->map->map[data->p_y][data->p_x] == 'E), and if the player has not collected all required items
  (data->collected != data->map->collectables`).*/
	if (pos == 'y' && data->map->map[data->p_y][data->p_x] == 'E'
		&& data->collected != data->map->collectables)
		ft_putstr("Collect all devils fruits before leaving\n");

/*Checks if the movement is horizontal (pos == 'x'), if the player's current position is an exit
  (data->map->map[data->p_y][data->p_x] == 'E), and if the player has not collected all required items
  (data->collected != data->map->collectables`).*/
	else if (pos == 'x' && data->map->map[data->p_y][data->p_x] == 'E'
		&& data->collected != data->map->collectables)
		ft_putstr("Collect all devils fruits before leaving\n");
}


/*The ft_move function handles the player's movement within the game. It updates the player's position,
  handles the graphical updates, checks for interactions with game objects, and counts the number of moves made by the player.*/
void	ft_move(t_data *data, char pos, int dir)
{
/*Draws the background image at the player's current position to erase the player from their current location.*/
	mlx_put_image_to_window(data->mlx, data->win, data->img->background,
		(data->p_x * IMG_W), (data->p_y * IMG_H));
/*Calls ft_do_move to update the player's position based on the specified direction (pos and dir).*/
	ft_do_move(data, pos, dir);
/*Calls ft_do_exit_move to check if the player is attempting to exit the game area without
  collecting all required items and display a message if so.*/
	ft_do_exit_move(data, pos);
/*Calls ft_player_move to draw the player at the new position based on the direction of movement.*/
	ft_player_move(data, pos, dir);
/*Checks if the player has moved to a position with a collectable item ('C').
  If true, calls ft_collect to handle the collection of the item and update the game state.*/
	if (data->map->map[data->p_y][data->p_x] == 'C')
		ft_collect(data, pos, dir);

/*Calls mlx_do_sync to force the display to update, ensuring all graphical changes are rendered.*/
	mlx_do_sync(data->mlx);
	ft_putstr("You did ");

/*Update Move Counter*/
	ft_printnbr(++data->counter);
	ft_putstr(" moves \r");
}
