/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sphere_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 15:20:01 by msidqi            #+#    #+#             */
/*   Updated: 2019/07/17 15:21:43 by msidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgl.h"

/*
** a=dot(B,B)
** b=2⋅dot(B,A−C)
** c=dot(A−C,A−C)−r2
** With the above parameterization, the quadratic formula is:
** t = (−b±b2−4ac) / (√2a)
*/

int				ft_sphere_inter(t_ray *ray, t_sphere *sp)
{
	double t[2];
	double discr;
	double abc[3];
	t_vec4 k;

	k = ft_vec4_sub(ray->origin, sp->center);
	abc[0] = ft_vec4_dot_product(ray->dir, ray->dir);
	abc[1] = 2 * ft_vec4_dot_product(ray->dir, k);
	abc[2] = ft_vec4_dot_product(k, k) - sp->radius * sp->radius;
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
** called foreach pixel
**	foreach light
**	get r_light and normal_sphere(calculate once)
**	check intersection with all objects,
** 		if : (hidden from light source by an obj) then :(its spec/diffuse += 0)
**	else : computed specular,
**		diffuse (light pixel, if : distance to light < (distance to obj == t))
**	ADD to return value
**
**	after foreach loop, add ambient
*/

static t_vec4	ft_get_sphere_normal(t_ray *ray, t_sphere *sp)
{
	return (ft_vec4_normalize(
		ft_vec4_sub(ft_vec4_add(ray->origin,
			ft_vec4_scalar(ray->dir, ray->t)), sp->center)));
}

unsigned int	ft_sphere_shader(t_data *data, t_ray *ray, t_sphere *sp)
{
	t_shader_x	sh_x;
	t_list		*l_lst;
	t_vec4		sp_nor;
	t_vec4		ds[2];

	sh_x.diff = ft_create_vec4(0.0, 0.0, 0.0, 0.0);
	sh_x.spec = ft_create_vec4(0.0, 0.0, 0.0, 0.0);
	l_lst = data->light_list;
	sp_nor = ft_get_sphere_normal(ray, sp);
	ds[0] = sp->diffuse;
	ds[1] = ft_create_vec4(sp->specular, sp->specular,
			sp->specular, sp->specular);
	sh_x = ft_ray_inter_lights(data, sp_nor, ray, ds);
	return (ft_compute_shader(sp->color, &sh_x));
}
