/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utenret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 16:30:00 by utenret           #+#    #+#             */
/*   Updated: 2023/01/16 16:30:32 by utenret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"


int	is_window_closed(t_data *img)
{
    return (mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length, &img->endian) != NULL);
}

int loop_hook(t_data *img)
{
    if(is_window_closed(img))
        return (0);
    return (1);
}

int is_open(t_data *img)
{
     printf("WTHSDSJFOIDSJFOSIDJFOIDS======%s|||||\n", mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length, &img->endian));
    return (mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length, &img->endian) != NULL);
}
