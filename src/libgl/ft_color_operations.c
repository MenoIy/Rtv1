/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_color_operations.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 15:26:31 by msidqi            #+#    #+#             */
/*   Updated: 2019/07/24 18:05:31 by kdaou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgl.h"

unsigned	int	ft_color_rgb_scalar(unsigned int color, double r,
		double g, double b)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)&color;
	ptr[2] = (ptr[2] * r) > 255 ? 255 : (ptr[2] * r);
	ptr[1] = (ptr[1] * g) > 255 ? 255 : (ptr[1] * g);
	ptr[0] = (ptr[0] * b) > 255 ? 255 : (ptr[0] * b);
	return (color);
}

/*
** memory representation of colors in little endian && big endian
** 		A		R		G		B
** 00000000 00000000 00000000 00000000
**	R is the biggest color value
**	Since we're working on a little endian OS and server X is also little e
**	we get access to the smaller value first.
**	This doesn't make difference when working bits wise, only bytes wise,
**	ptr[0] contains B's value && ptr[3] == alpha
*/

int				ft_color_add(unsigned int color1, unsigned int color2)
{
	unsigned int a;
	unsigned int r;
	unsigned int g;
	unsigned int b;

	a = ((color2 >> 24) & 0xff) + ((color1 >> 24) & 0xff);
	r = ((color2 >> 16) & 0xff) + ((color1 >> 16) & 0xff);
	g = ((color2 >> 8) & 0xff) + ((color1 >> 8) & 0xff);
	b = (color2 & 0xff) + (color1 & 0xff);
	a = a > 255 ? 255 : a;
	r = r > 255 ? 255 : r;
	g = g > 255 ? 255 : g;
	b = b > 255 ? 255 : b;
	return ((a << 24) | (r << 16) | (g << 8) | b);
}

/*
**	ALPHA :
**	int i = -1, j;
**	while (++i < HEIGHT)
**	{
**		j = -1;
**		while (++j < WIDTH)
**		{
**			mlx_pixel_put(data.mlx, data.win, j, i, 0xAAFF0000);
**		}
**	}
*/
