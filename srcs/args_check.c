/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utenret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 15:34:52 by utenret           #+#    #+#             */
/*   Updated: 2023/01/18 19:29:09 by utenret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

bool	can_read_and_split_map(char *filename, char ***split_map)
{
	char	*res;
	char	*res2;
	int		fd;

	fd = open(filename, O_RDONLY);
	res = get_next_line(fd);
	res2 = get_next_line(fd);
	while(res2 != NULL)
	{
		res = ft_strjoin(res, res2);
		if (res2 != NULL)
			free(res2);
		res2 = get_next_line(fd);
	}
	*split_map = ft_split(res, '\n');
	free(res);
	if (split_map == NULL)
		return (false);
	close(fd);
	return (true);
}

void	ft_free_split_map(char ***split_map)
{
	int	i;

	i = 0;
	while ((*split_map)[i] != NULL)
	{
		free((*split_map)[i]);
		i++;
	}
	free(*split_map);
}

bool	is_map_big_enough(int i, int len)
{
	if (i < 3 || len < 3)
		return (false);
	return (true);
}

bool	is_map_rectangular(char **split)
{
	int		i;
	size_t	len;
	size_t	len2;

	i = 0;
	len = ft_strlen(split[i]);
	while (split[i] != NULL)
	{
		len2 = ft_strlen(split[i]);
		if (len != len2)
			return (false);
		i++;
	}
	if (is_map_big_enough(i, ft_strlen(split[0])) == false)
		return (false);
	return (true);
}

bool	do_top_and_bottom_wall_exist(char **split)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (split[j] != NULL)
		j++;
	j--;
	while(split[0][i] != '\0')
	{
		if(split[0][i] != '1')
			return (false);
		i++;
	}
	i = 0;
	while(split[j][i] != '\0')
	{
		if(split[j][i] != '1')
			return (false);
		i++;
	}
	return (true);
}

bool	do_middle_wall_exist(char **split)
{
	int	len;
	int	j;

	len = ft_strlen(split[0]) - 1;
	j = 0;
	while(split[j] != NULL)
	{
		if (split[j][0] != '1' || split[j][len] != '1')
			return (false);
		j++;	
	}
	return (true);
}

bool	is_map_walled(char **split)
{
	if (do_top_and_bottom_wall_exist(split) == false)
		return (false);
	else if (do_middle_wall_exist(split) == false)
	{
		printf("braaaaaaaaaaaaaaaaaah\n");
		return (false);
	}
	return (true);
}

bool	map_has_exactly_one_exit_and_start(char **split)
{
	int		j;
	int		i;
	int		exit_count;
	int		start_count;

	j = 0;
	i = 0;
	exit_count = 0;
	start_count = 0;
	while (split[j] != NULL)
	{
		while (split[j][i] != '\0')
		{
			if (split[j][i] == 'P')
				start_count++;
			if (split[j][i] == 'E')
				exit_count++;
			i++;
		}
		i = 0;
		j++;
	}
	if (start_count != 1 || exit_count != 1)
		return (false);
	return (true);
}


bool	map_contains_at_least_one_collectible(char **split)
{
	int		j;
	int		i;
	int		collectible_count;

	j = 0;
	i = 0;
	collectible_count = 0;
	while (split[j] != NULL)
	{
		while (split[j][i] != '\0')
		{
			if (split[j][i] == 'C')
				collectible_count++;
			i++;
		}
		i = 0;
		j++;
	}
	if (collectible_count == 0)
		return (false);
	return (true);
}

bool	does_map_contain_only_allowd_char(char **split)
{
	int	j;
	int	i;

	i = 0;
	j = 0;
	while (split[j] != NULL)
	{
		while (split[j][i] != '\0')
		{
			if (ft_strchr("01CEP", split[j][i]) == NULL)
				return (false);
			i++;
		}
	i = 0;
	j++;
	}
	if (map_has_exactly_one_exit_and_start(split) == false)
	{
		printf("hobbbbiiitjouflluuu\n");
		return (false);
	}
	if (map_contains_at_least_one_collectible(split) == false)
	{
		printf("where are the coinsss mangooo\n");
		return (false);
	}
	return (true);
}

bool	is_map_valid(char **split_map)
{
	int		i;

	i = 0;
	if (does_map_contain_only_allowd_char(split_map) == false)
	{
		printf("gagacagagagagaga\n");
		return (false);
	}
	else if (is_map_rectangular(split_map) == false)
	{
		printf("dwombcuntttt\n");
		return (false);
	}
	else if (is_map_walled(split_map) == false)
	{
		printf("stooopiddddddd\n");
		return (false);
	}
	else if (can_collect_and_exit(split_map) == false)
	{
		printf("Bruh get this map some air and some orange juice\n");
		return (false);
	}		
		return (true);
}

bool	is_filename_valid(char *filename)
{
	const char	*ext_name = ".ber";	
	const int	len = ft_strlen(filename);
	size_t		i;

	if (len < 5)
		return (false);
	filename += len - 4;
	i = 0;
	while (filename[i] != '\0')
	{
		if (filename[i] != ext_name[i])
			return (false);
		i++;
	}
	return (true);
}

bool	is_input_valid(int ac, char **av)
{
	char	*res;
	int		fd;

	fd = open(av[1], O_RDONLY);
	res = get_next_line(fd);
	if (ac != 2)
		ft_printf("Error.\nPlease input as parameter [ONE] map description file ending with the .ber extension.\n");
	else if (is_filename_valid(av[1]) == false)
		ft_printf("Error.\nPlease input as parameter one map description file ending with the .ber extension.\n");
	else if (fd == -1)
		ft_printf("Error.\nCan't open the file. Input must be a valid existing file, not a directory, ending with the .ber extension.\n");
	else if (res == NULL)
		ft_printf("Error.\nReading failed. Input must be a valid file, not a directory, ending with the .ber extension.\n");
	else
	{
		free(res);
		res = get_next_line(fd);
		while(res != NULL)
		{
			free(res);
			res = get_next_line(fd);
		}
		close(fd);
		return (true);
	}
	return (false);
}
