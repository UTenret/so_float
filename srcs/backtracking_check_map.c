/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backtracking_check_map.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utenret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 13:05:28 by utenret           #+#    #+#             */
/*   Updated: 2023/01/18 19:46:39 by utenret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"


bool	found_next_collectible_or_exit(char **split, t_grid *grid, int *x, int *y)
{
	while (split[*y] != NULL)
	{
		while (split[*y][*x] != '\0')
		{
			if (ft_strchr("CE", split[*y][*x]) != NULL)
			{
				grid->dest_y = *y;
				grid->dest_x = *x;
				(*x)++;
				printf("grid->dest_y ===%d\n", grid->dest_y);
				printf("grid->dest_x ===%d\n", grid->dest_x);
				return (true);
			}
			(*x)++;
		}
		*x = 0;
		(*y)++;
	}
	return (false);
}

bool	is_dest_reachable(char **split, t_grid *grid, int x, int y)
{
	if (x == grid->dest_x && y == grid->dest_y)
		return (true);
	if (x >= grid->width || y >= grid->height)
		return (false);
	if (x < 0 || y < 0)
		return (false);
	if (grid->visited[y][x] == true)
		return (false);
	if (split[y][x] == '1' || split[y][x] == 'E')
		return (false);
	grid->visited[y][x] = true;
	if (is_dest_reachable(split, grid, x + 1, y) == true)
		return (true);
	if (is_dest_reachable(split, grid, x - 1, y) == true)
		return (true);
	if (is_dest_reachable(split, grid, x, y + 1) == true)
		return (true);
	if (is_dest_reachable(split, grid, x, y - 1) == true)
		return (true);	
	return (false);
}

void	ft_bzero_visited(t_grid *grid)
{
	int		i;

	i = 0;
	while (i < grid->height)
	{
		ft_bzero(grid->visited[i], grid->width);
		i++;
	}
}

bool	is_it_backtrackable(char **split, t_grid *grid)
{
	int	x;
	int	y;

	y = 0;
	x = 0;
	printf("312313grid->start_x ===%d\n", grid->start_x);
	printf("3213123grid->start_y ===%d\n", grid->start_y);
	while (found_next_collectible_or_exit(split, grid, &x, &y) == true)
	{
		printf("---------grid->start_x ===%d\n", grid->start_x);
		printf("---------grid->start_y ===%d\n", grid->start_y);
		if (is_dest_reachable(split, grid, grid->start_x, grid->start_y) == false)
		{
			printf("losamaxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
			return (false);
		}
		else
		{
			ft_bzero_visited(grid);
			printf("winamaxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
		}
			
	}
	return (true);
}

void	find_player_start(char **split, t_grid *grid)
{
	int		j;
	int		i;

	j = 0;
	i = 0;
	while (split[j] != NULL)
	{
		while (split[j][i] != '\0')
		{
			if (split[j][i] == 'P')
			{
				grid->start_x = i;
				grid->start_y = j;
				printf("grid->start_x ===%d\n", grid->start_x);
				printf("grid->start_y ===%d\n", grid->start_y);
				return;
			}
			i++;
		}
		i = 0;
		j++;
	}
}

bool	initialize_grid(char **split, t_grid *grid)
{
	int	i;
	int	j;

	i = 0;
	while(split[i] != NULL)
		i++;
	grid->width = ft_strlen(split[0]);
	grid->height = i;
	grid->visited = ft_calloc(i, sizeof(bool *));
	if (grid->visited == NULL)
		return (false);
	j = 0;
	while(j < i)
	{
		grid->visited[j] = ft_calloc(ft_strlen(split[0]) + 1, sizeof(bool));
		if (grid->visited[j] == NULL)
			return (false);
		j++;
	}
	grid->dest_x = 0;
	grid->dest_y = 0;
	find_player_start(split, grid);
	return (true);
}

void	free_grid(t_grid *grid)
{
	int	i;

	i = 0;
	printf("grid->height ====%d\n", grid->height);
	while (i < grid->height)
	{
		free(grid->visited[i]);
		i++;
	}
	free(grid->visited);
}

bool	can_collect_and_exit(char **split)
{
	t_grid grid;

	initialize_grid(split, &grid);
	if (is_it_backtrackable(split, &grid) == false)
	{
		printf("grid.height ==%d\n", grid.height);
		free_grid(&grid);
		return (false);
	}
	else
	{
		printf("grid.width ==%d\n", grid.width);
		free_grid(&grid);
		return (true);
	}
}
