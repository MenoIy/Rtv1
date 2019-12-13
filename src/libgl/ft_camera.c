/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_camera.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 15:56:57 by msidqi            #+#    #+#             */
/*   Updated: 2019/07/25 18:57:08 by kdaou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgl.h"

static double	ft_map(int x_or_y, double size, int width_or_height)
{
	return (x_or_y * size / width_or_height - (size / 2));
}

void			ft_camera_ray(t_ray *ray, t_camera *cam, int x, int y)
{
	t_vec4 new_left;
	t_vec4 new_up;
	t_vec4 new_forw;
	t_vec4 left_up;

	new_left = ft_vec4_scalar(cam->left, ft_map(x - ((WIDTH - HEIGHT) / 2),
				cam->bigl, WIDTH * ASPECT_RATIO));
	new_up = ft_vec4_scalar(cam->up, ft_map(y, cam->l, HEIGHT));
	new_forw = ft_vec4_scalar(cam->forward, cam->focal_length);
	left_up = ft_vec4_add(new_up, new_left);
	ray->dir = ft_vec4_normalize(ft_vec4_add(left_up, new_forw));
	ray->origin = ft_create_vec4(cam->pos.x, cam->pos.y, cam->pos.z, 0);
	ray->t = FAR;
}

void			ft_camera(t_data *data, t_vec4 position, t_vec4 lookat)
{
	t_vec4 forward;
	t_vec4 camera_up;
	t_vec4 camera_left;
	t_vec4 up;

	data->cam.l = 1;
	data->cam.bigl = 1;
	data->cam.pos = position;
	data->cam.to = lookat;
	forward = ft_vec4_normalize(ft_vec4_sub(data->cam.to, data->cam.pos));
	if (forward.x == 0 && forward.y == 1 && forward.z == 0)
		up = ft_vec4_normalize(ft_create_vec4(1, 0, 0, 0));
	else
		up = ft_vec4_normalize(data->cam.absolute_up);
	camera_left = ft_vec4_cross_product(up, forward);
	camera_up = ft_vec4_cross_product(forward, camera_left);
	data->cam.up = ft_vec4_normalize(camera_up);
	data->cam.left = ft_vec4_normalize(camera_left);
	data->cam.forward = forward;
}
