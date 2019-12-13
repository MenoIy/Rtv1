/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_plane_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 15:09:59 by msidqi            #+#    #+#             */
/*   Updated: 2019/07/24 18:15:15 by kdaou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgl.h"

/*
** a plane is defined by a normal and a point1.
** if dot product between the vector(point1 - point2)
** and the normal == 0 then that point2 is part of the plane.
** (p1 − p2)⋅n=0
**
** if we assume that a ray and the plane intersects in point2
** ((origin + t * dir) − p2)⋅n = 0
** and calculate t(the distance from the ray's origin and point2)
** we can calculate t for point2.
** t = (p0 − origin)⋅n / (dir⋅n)
*/

int				ft_plane_inter(t_ray *ray, t_plane *plane)
{
	t_vec4	k;
	double	t0;
	double	dot;

	dot = ft_vec4_dot_product(ray->dir, plane->normal);
	if (dot == 0)
		return (0);
	k = ft_vec4_sub(plane->point, ray->origin);
	t0 = ft_vec4_dot_product(k, plane->normal) / dot;
	if (t0 > NEAR && t0 < ray->t)
	{
		ray->t = t0;
		return (1);
	}
	return (0);
}

static t_vec4	ft_get_plane_normal(t_ray *ray, t_plane *pl)
{
	return (ft_vec4_dot_product(ray->dir,
				pl->normal) < 0 ?
			pl->normal : ft_vec4_scalar(pl->normal, -1));
}

unsigned int	ft_plane_shader(t_data *data, t_ray *ray, t_plane *pl)
{
	t_shader_x	sh_x;
	t_list		*l_lst;
	t_vec4		pl_nor;
	t_vec4		ds[2];

	sh_x.diff = ft_create_vec4(0.0, 0.0, 0.0, 0.0);
	sh_x.spec = ft_create_vec4(0.0, 0.0, 0.0, 0.0);
	l_lst = data->light_list;
	pl_nor = ft_get_plane_normal(ray, pl);
	ds[0] = pl->diffuse;
	ds[1] = ft_create_vec4(pl->specular, pl->specular,
			pl->specular, pl->specular);
	sh_x = ft_ray_inter_lights(data, pl_nor, ray, ds);
	return (ft_compute_shader(pl->color, &sh_x));
}
