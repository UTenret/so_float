/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utenret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 16:50:05 by utenret           #+#    #+#             */
/*   Updated: 2023/01/19 20:34:31 by utenret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "libft.h"
# include "mlx.h"
# include "mlx_int.h"

# define ESCAPE_KEY 65307
# define W_KEY 119
# define A_KEY 97
# define S_KEY 115
# define D_KEY 100

# define TILE_SIZE 64

typedef struct	s_data {
	void	**img;
	int		img_count;
	void	*mlx;
	void	*win;
	int		player_x;
	int		player_y;
	int		step_count;
	int		c_count;
	char	**split_map;
}				t_data;

typedef struct	s_grid {
	int	height;	
	int	width;
	bool **visited;
	int	dest_x;
	int	dest_y;
	int	start_x;
	int	start_y;
}				t_grid;

bool	is_input_valid(int ac, char **av);
void	ft_free_split_map(char ***split_map);
bool	can_collect_and_exit(char **split);
bool	can_read_and_split_map(char *filename, char ***split_map);
bool	is_map_valid(char **split_map);

#endif
