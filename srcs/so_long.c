/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utenret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 19:31:03 by utenret           #+#    #+#             */
/*   Updated: 2023/01/19 20:40:18 by utenret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_destroy_n_quit(t_data *img)
{
	mlx_destroy_image(img->mlx, img->img[0]);
	mlx_destroy_image(img->mlx, img->img[1]);
	mlx_destroy_image(img->mlx, img->img[2]);
	mlx_destroy_image(img->mlx, img->img[3]);
	mlx_destroy_image(img->mlx, img->img[4]);
	mlx_destroy_window(img->mlx, img->win);
	mlx_destroy_display(img->mlx);
	free(img->mlx);
	free(img->img);
	ft_free_split_map(&(img->split_map));
    exit(0);
}

int	close_window(t_data *img)
{
	free_destroy_n_quit(img);
	return (0);
}

void	init_window_size(t_data *img, char **split)
{
	int	j;
	int	height;
	int	width;

	j = 0;
	while (split[j] != NULL)
		j++;
	img->img_count = j * ft_strlen(split[0]);
	height = j * TILE_SIZE;
	width = ft_strlen(split[0]) * TILE_SIZE;
	img->win = mlx_new_window(img->mlx, width, height, "Hello");
}

void	init_mlx(t_data *img, char **split)
{
	img->mlx = mlx_init();
	init_window_size(img, split);
}

void	put_correct_img(t_data *img, char c, int i, int j)
{
	if (c == '1')
		mlx_put_image_to_window(img->mlx, img->win, img->img[3], i, j);
	else if (c == '0')
		mlx_put_image_to_window(img->mlx, img->win, img->img[4], i, j);
	else if (c == 'P')
		mlx_put_image_to_window(img->mlx, img->win, img->img[2], i, j);
	else if (c == 'C')
		mlx_put_image_to_window(img->mlx, img->win, img->img[0], i, j);
	else if (c == 'E')
		mlx_put_image_to_window(img->mlx, img->win, img->img[1], i, j);
}

void	put_img_to_w(t_data *img, char **split)
{
	int	j;
	int	i;
	int	k;
	int	l;

	j = 0;
	i = 0;
	k = 0;
	l = 0;
	while (split[j] != NULL)
	{
		while(split[j][i] != '\0')
		{
			put_correct_img(img, split[j][i], k, l);
			k += TILE_SIZE;
			i++;
		}
		i = 0;
		k = 0;
		l += TILE_SIZE;
		j++;;
	}
}

void	init_player_pos(t_data *img, char **split)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (split[j] != NULL)
	{
		while (split[j][i] != '\0')
		{
			if (split[j][i] == 'P')
			{
				img->player_y = j;		
				img->player_x = i;		
				return;
			}
			i++;
		}
		i = 0;
		j++;
	}
}

void	init_c_count(t_data *img, char **split)
{
	int	j;
	int	i;

	img->c_count = 0;
	i = 0;
	j = 0;
	while (split[j] != NULL)
	{
		while (split[j][i] != '\0')
		{
			if (split[j][i] == 'C')
				img->c_count++;
			i++;
		}
		i = 0;
		j++;
	}
}

void	init_map(t_data *img, char **split)
{
	int	h;
	int	w;

	(void)split;
	h = 0;
	w = 0;
	img->img = (void**)malloc(sizeof(void*) * 5);

	img->img[0] = mlx_xpm_file_to_image(img->mlx, "xpm/collectible_enhanced.xpm", &w, &h);
	img->img[1] = mlx_xpm_file_to_image(img->mlx, "xpm/exit_enhanced.xpm", &w, &h);
	img->img[2] = mlx_xpm_file_to_image(img->mlx, "xpm/player_enhanced.xpm", &w, &h);
	img->img[3] = mlx_xpm_file_to_image(img->mlx, "xpm/wall_enhanced.xpm", &w, &h);
	img->img[4] = mlx_xpm_file_to_image(img->mlx, "xpm/grass_enhanced.xpm", &w, &h);
	put_img_to_w(img, split);
	init_player_pos(img, split);
	init_c_count(img, split);
	img->step_count = 0;
}

void	update_img(t_data *img, char c, int y, int x)
{
	put_correct_img(img, c, x * TILE_SIZE, y * TILE_SIZE);		
}


void	update_w_key_img_hook(t_data *img)
{
	const int	y = img->player_y;
	const int	x = img->player_x;

	if (img->split_map[y - 1][x] == '0' || img->split_map[y - 1][x] == 'C')
	{
		img->player_y--;
		update_img(img, '0', y, x);
		update_img(img, 'P', y - 1, x);
		img->step_count++;
		if (img->split_map[y - 1][x] == 'C')
		{
			img->split_map[y - 1][x] = '0';
			img->c_count--;
		}
		ft_printf("Current step count = %d\n", img->step_count);
	}
	else if (img->split_map[y - 1][x] == 'E' && img->c_count == 0)
	{
		ft_printf("Current step count = %d\n", img->step_count + 1);
		free_destroy_n_quit(img);
	}
}

void	update_s_key_img_hook(t_data *img)
{
	const int	y = img->player_y;
	const int	x = img->player_x;

	if (img->split_map[y + 1][x] == '0' || img->split_map[y + 1][x] == 'C')
	{
		img->player_y++;
		update_img(img, '0', y, x);
		update_img(img, 'P', y + 1, x);
		img->step_count++;
		if (img->split_map[y + 1][x] == 'C')
		{
			img->split_map[y + 1][x] = '0';
			img->c_count--;
		}
		ft_printf("Current step count = %d\n", img->step_count);
	}
	else if (img->split_map[y + 1][x] == 'E' && img->c_count == 0)
	{
		ft_printf("Current step count = %d\n", img->step_count + 1);
		free_destroy_n_quit(img);
	}
}

void	update_d_key_img_hook(t_data *img)
{
	const int	y = img->player_y;
	const int	x = img->player_x;

	if (img->split_map[y][x + 1] == '0' || img->split_map[y][x + 1] == 'C')
	{
		img->player_x++;
		update_img(img, '0', y, x);
		update_img(img, 'P', y, x + 1);
		img->step_count++;
		if (img->split_map[y][x + 1] == 'C')
		{
			img->split_map[y][x + 1] = '0';
			img->c_count--;
		}
		ft_printf("Current step count = %d\n", img->step_count);
	}
	else if (img->split_map[y][x + 1] == 'E' && img->c_count == 0)
	{
		ft_printf("Current step count = %d\n", img->step_count + 1);
		free_destroy_n_quit(img);
	}
}

void	update_a_key_img_hook(t_data *img)
{
	const int	y = img->player_y;
	const int	x = img->player_x;

	if (img->split_map[y][x - 1] == '0' || img->split_map[y][x - 1] == 'C')
	{
		img->player_x--;
		update_img(img, '0', y, x);
		update_img(img, 'P', y, x - 1);
		img->step_count++;
		if (img->split_map[y][x - 1] == 'C')
		{
			img->split_map[y][x - 1] = '0';
			img->c_count--;
		}
		ft_printf("Current step count = %d\n", img->step_count);
	}
	else if (img->split_map[y][x - 1] == 'E' && img->c_count == 0)
	{
		ft_printf("Current step count = %d\n", img->step_count + 1);
		free_destroy_n_quit(img);
	}
}

int	update_img_hook(int key, t_data *img)
{
	if (key == ESCAPE_KEY)
		free_destroy_n_quit(img);
	if (key == S_KEY)
		update_s_key_img_hook(img);	
	else if (key == W_KEY)
		update_w_key_img_hook(img);	
	else if (key == D_KEY)
		update_d_key_img_hook(img);	
	else if (key == A_KEY)
		update_a_key_img_hook(img);	
	return (0);
}


void	init_hooks(t_data *img)
{
	mlx_hook(img->win, 2, 1, update_img_hook, img);
	mlx_hook(img->win, 17, 0, close_window, img);
}

int	main(int ac, char **av)
{
	t_data	img;

	img.split_map = NULL;
	if (is_input_valid(ac, av) == false)
	{
		ft_printf("Error.\nInvalid input.\n");
		exit(1);
	}
	if (can_read_and_split_map(av[1], &(img.split_map)) == false)
	{
		ft_free_split_map(&(img.split_map));
		return (false);
	}
	if (is_map_valid(img.split_map) == false)
	{
		ft_printf("Error.\nThis is not a valid map.\n");
		ft_free_split_map(&(img.split_map));
		return (false);
	}
	else
	{
		init_mlx(&img, img.split_map);
		init_map(&img, img.split_map);
		img.split_map[img.player_y][img.player_x] = '0';
		init_hooks(&img);
	}
	mlx_loop(img.mlx);	
	exit(0);
}

