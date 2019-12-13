/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cylinder_functions.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 15:11:54 by msidqi            #+#    #+#             */
/*   Updated: 2019/07/24 18:09:54 by kdaou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgl.h"

/*
** const = ray.origin - cylinder.point;
** a = ray.dir ⋅ ray.dir - (ray.dir ⋅ axis)**2
**
** b/2 = ray.dir ⋅ const - (ray.dir ⋅ axiis) * (const ⋅ axis)
**
** c = const ⋅ const - (const ⋅ axis)**2 - radius**2
*/

int				ft_cylinder_inter(t_ray *ray, t_cylinder *cyl)
{
	double t[2];
	double discr;
	double abc[3];
	t_vec4 tmp;

	tmp = ft_vec4_sub(ray->origin, cyl->point);
	abc[0] = ft_vec4_dot_product(ray->dir, ray->dir)
		- pow(ft_vec4_dot_product(ray->dir, cyl->axis), 2);
	abc[1] = (ft_vec4_dot_product(ray->dir, tmp)
			- ft_vec4_dot_product(ray->dir, cyl->axis)
			* ft_vec4_dot_product(tmp, cyl->axis)) * 2;
	abc[2] = ft_vec4_dot_product(tmp, tmp) - pow(ft_vec4_dot_product(tmp,
								cyl->axis), 2) - cyl->radius * cyl->radius;
	discr = abc[1] * abc[1] - 4 * abc[0] * abc[2];
	if (discr < 0)
		return (0);
	t[0] = (-abc[1] + sqrt(discr)) / (2 * abc[0]);
	t[1] = (-abc[1] - sqrt(discr)) / (2 * abc[0]);
	t[0] = t[0] < t[1] && t[0] > NEAR ? t[0] : t[1];
	if (t[0] > NEAR && t[0] < ray->t)
	{
		ray->t = t[0];
		return (1);
	}
	return (0);
}

/*
** 1- P = intersection point = O + t * D;
**
** 2- A = C + m * axis; => where vector (P - A) is
** 		perpendicular to normal = the point where ((P - A) ⋅ axis) is 0;
**
** 3- (P - (C + m * axis)) ⋅ axis == 0
** (P - C - m * axis) ⋅ axis == 0
** (P - C) ⋅ axis == m * (axis ⋅ axis)     &&    (axis ⋅ axis == 1)
** m == (P - C) ⋅ axis;
**
** ==> A == C + ((P - C) ⋅ axis) * axis
**
**
** normal == P - A;
** normal == O + t * D - (C + ((P - C) ⋅ axis) * axis)
**
** normal == O + t * D - C - ((P - C) ⋅ axis) * axis)
** normal = P - C - ((P - C) . axe ) * axe;
**
** => normal = (r_light.origin) - (cylinder.point
** 			+ ft_vec4_dot_product(ft_vec4_sub(r_light.origin, cylinder.point),
**												cylinder.axis) * cylinder.axis)
*/

static t_vec4	ft_get_cylinder_normal(t_ray *ray, t_vec4 axis, t_vec4 c)
{
	t_vec4	p_sub_c;
	double	m;
	t_vec4	x;

	x = ft_vec4_sub(ray->origin, c);
	m = ft_vec4_dot_product(ray->dir, ft_vec4_scalar(axis, ray->t)) +
		ft_vec4_dot_product(x, axis);
	p_sub_c = ft_vec4_sub(ft_vec4_add(ray->origin,
				ft_vec4_scalar(ray->dir, ray->t)), c);
	return (ft_vec4_normalize(ft_vec4_sub(p_sub_c, ft_vec4_scalar(axis, m))));
}

unsigned int	ft_cylinder_shader(t_data *data, t_ray *ray, t_cylinder *cyl)
{
	t_shader_x	sh_x;
	t_list		*l_lst;
	t_vec4		cyl_nor;
	t_vec4		ds[2];

	l_lst = data->light_list;
	cyl_nor = ft_get_cylinder_normal(ray, cyl->axis, cyl->point);
	ds[0] = cyl->diffuse;
	ds[1] = ft_create_vec4(cyl->specular, cyl->specular,
			cyl->specular, cyl->specular);
	sh_x = ft_ray_inter_lights(data, cyl_nor, ray, ds);
	return (ft_compute_shader(cyl->color, &sh_x));
}
