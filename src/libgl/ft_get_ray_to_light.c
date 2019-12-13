/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_ray_to_light.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 15:53:39 by msidqi            #+#    #+#             */
/*   Updated: 2019/07/17 15:56:10 by msidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgl.h"

t_ray	ft_get_ray(t_data *data, t_vec4 *view_window_pos)
{
	t_ray ray;

	ray.dir = ft_vec4_normalize(ft_vec4_sub((*view_window_pos),
				data->cam.pos));
	ray.origin = ft_create_vec4(data->cam.pos.x,
			data->cam.pos.y, data->cam.pos.z, 0);
	return (ray);
}

/*
** tmp, calculating position vector from camera to inter_point
** intersection point calculated
** 							(pos vec of cam + cam_to_inter = inter_vec_pos)
*/

t_ray	ft_get_ray_to_light(t_ray *ray, t_light *light)
{
	t_vec4	inter_point;
	t_ray	r_light;

	inter_point = ft_vec4_add(ray->origin, ft_vec4_scalar(ray->dir, ray->t));
	r_light.origin = inter_point;
	r_light.dir = ft_vec4_normalize(ft_vec4_sub(light->origin,
														r_light.origin));
	return (r_light);
}
