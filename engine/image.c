/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolomer <ncolomer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 00:30:21 by ncolomer          #+#    #+#             */
/*   Updated: 2019/11/06 20:28:09 by ncolomer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

void
    init_image(t_window *window, t_image *img)
{
    img->img = mlx_new_image(window->ptr, window->size.x, window->size.y);
    img->ptr = mlx_get_data_addr(
        img->img, &img->bpp, &img->size_line, &img->endian);
}

void
    destroy_image(t_window *window, t_image *img)
{
    mlx_destroy_image(window->ptr, img->img);
}
