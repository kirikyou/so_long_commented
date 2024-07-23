/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeulema <jmeulema@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 17:42:28 by jmeulema          #+#    #+#             */
/*   Updated: 2023/03/02 13:41:26 by jmeulema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*The duplicate_map function creates a duplicate (deep copy) of the 2D map array from the data structure.
  This is often useful for operations like pathfinding or manipulation without altering the original map.*/
char	**duplicate_map(t_data *data)
{
	int		i;
	int		j;
	char	**my_map;

	i = 0;

/*Counts the number of rows in the original map. i will hold the number of rows after the loop.*/
	while (data->map->map[i])
		i++;

/*Allocates memory for the array of row pointers, with one extra pointer for the terminating NULL.*/
	my_map = malloc(sizeof(char *) * (i + 1));
	if (!my_map)
		return (NULL);

/*Copy Each Row:*/
	i = -1;
	while (data->map->map[++i])
	{
		j = -1;

	/*Allocates memory for each row, with space for the null terminator.*/
		my_map[i] = malloc(sizeof(char) * (ft_strlen(data->map->map[i]) + 1));
		if (!(my_map[i]))
			return (NULL);
	/*Copies each character from the original map row to the duplicate map row.*/
		while (data->map->map[i][++j])
			my_map[i][j] = data->map->map[i][j];
		/*Ensures each row in the duplicate map is null-terminated.*/
		my_map[i][j] = 0;
	}
	
	/*Adds a terminating NULL pointer to the end of the my_map array, indicating the end of the rows.*/
	my_map[i] = 0;
	return (my_map);
}

/*The ft_path_help function is a helper function designed to assist in pathfinding within a 2D game map.
  It explores adjacent cells in the map recursively, marking visited cells and counting important elements like coins and exits.
  t_path *path: A pointer to a t_path structure that tracks the number of coins and exits encountered during the pathfinding.
  char **map: A 2D array representing the game map.
  int y: The current row index in the map.
  int x: The current column index in the map.*/
void	ft_path_help(t_path *path, char **map, int y, int x)
{
	/*f the cell to the right of the current cell (i.e., map[y][x + 1]) is not a wall ('1'):*/
	if (map[y][x + 1] != '1')
	{
		if (map[y][x + 1] == 'C')
			path->coins++;
		if (map[y][x + 1] == 'E')
			path->exit++;
			/*Set map[y][x + 1] to '1' to mark it as visited.*/
		map[y][x + 1] = '1';
		/*Recursive Call: Call ft_path to continue pathfinding from the new cell (y, x + 1).*/
		ft_path(path, map, y, x + 1);
	}

	/*f the cell to the left of the current cell (i.e., map[y][x - 1]) is not a wall ('1'):*/
	if (map[y][x - 1] != '1')
	{
		if (map[y][x - 1] == 'C')
			path->coins++;
		if (map[y][x - 1] == 'E')
			path->exit++;
		map[y][x - 1] = '1';
		ft_path(path, map, y, x - 1);
	}
}

/*The ft_path function is designed to perform a depth-first search (DFS) on the game map to find
  all possible paths from a given starting point. It marks cells as visited and counts specific
  elements (coins and exits) encountered during the search.*/
void	ft_path(t_path *path, char **map, int y, int x)
{
	/*If the cell below the current cell (i.e., map[y + 1][x]) is not a wall ('1'):*/
	if (map[y + 1][x] != '1')
	{
		if (map[y + 1][x] == 'C')
			path->coins++;
		if (map[y + 1][x] == 'E')
			path->exit++;
		map[y + 1][x] = '1';
		ft_path(path, map, y + 1, x);
	}
	/*If the cell above the current cell (i.e., map[y + 1][x]) is not a wall ('1'):*/
	if (map[y - 1][x] != '1')
	{
		if (map[y - 1][x] == 'C')
			path->coins++;
		if (map[y - 1][x] == 'E')
			path->exit++;
		map[y - 1][x] = '1';
		ft_path(path, map, y - 1, x);
	}
	/*calls the ft_path_help function, which checks the cells to the left and right of the current cell
	 and performs similar operations as described above.*/
	ft_path_help(path, map, y, x);
}


/*The check_paths function is designed to verify if all the collectable items and the exit are reachable
  from a given starting position on the game map.It does this by duplicating the map,performing a depth-first search (DFS)
  from the starting position, and checking if the number of collected items and the exit found match the expected values.*/
int	check_paths(t_data *data, int pos_y, int pos_x, int collectables)
{
	char	**dup;
	t_path	path;

	dup = duplicate_map(data);
	/*Initializes a t_path structure to keep track of the number of coins and the exit found during the pathfinding process.*/
	path.coins = 0;
	path.exit = 0;
	/*Calls the ft_path function to perform a depth-first search starting from the given position (pos_y, pos_x).
	  The ft_path function will update the path structure with the number of coins and exits found.*/
	ft_path(&path, dup, pos_y, pos_x);
	/*Frees the memory allocated for the duplicated map to avoid memory leaks.
	  It iterates through each row of the duplicated map, frees it, and finally frees the array of pointers.*/
	pos_y = 0;
	while (dup[pos_y])
		free(dup[pos_y++]);
	free(dup);
	
	/*Compares the number of coins found during the pathfinding (path.coins) with the expected number of collectables (collectables).
	  Checks if exactly one exit (path.exit == 1) was found during the pathfinding.
	  Returns 1 if both conditions are met, indicating that all collectables and the exit are reachable. Otherwise, returns 0.*/
	return (path.coins == collectables && path.exit == 1);
}
