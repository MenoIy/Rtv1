/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_events_keyboard.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 13:27:08 by msidqi            #+#    #+#             */
/*   Updated: 2019/07/24 20:03:01 by kdaou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgl.h"

int			no_event_mouse_move(t_data *data)
{
	if (!ft_refresh_image(data))
	{
		ft_lstdel(&data->scene, &ft_del);
		ft_lstdel(&data->light_list, &ft_del);
		exit(1);
	}
	ft_camera(data, data->cam.pos, data->cam.to);
	ft_draw(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img_ptr, 0, 0);
	return (0);
}

int			mouse_move(int x, int y, t_data *data)
{
	(void)x;
	(void)y;
	(void)data;
	return (0);
}

static void	ft_key_camera(int key_code, t_data *data)
{
	if (key_code == NUM_LOCK_2)
		data->cam.absolute_up = ft_create_vec4(0, 0, -1, 0);
	if (key_code == NUM_LOCK_8)
		data->cam.absolute_up = ft_create_vec4(0, 0, 1, 0);
	if (key_code == NUM_LOCK_4)
		data->cam.absolute_up = ft_create_vec4(-1, 0, 0, 0);
	if (key_code == NUM_LOCK_6)
		data->cam.absolute_up = ft_create_vec4(1, 0, 0, 0);
	if (key_code == NUM_LOCK_5)
		data->cam.absolute_up = ft_create_vec4(0, 1, 0, 0);
	if (key_code == NUM_LOCK_7)
		data->cam.absolute_up = ft_create_vec4(0, -1, 0, 0);
}

int			key_press(int key_code, t_data *data)
{
	if (key_code == 53 || !ft_refresh_image(data))
	{
		ft_lstdel(&data->scene, &ft_del);
		ft_lstdel(&data->light_list, &ft_del);
		exit(1);
	}
	ft_key_camera(key_code, data);
	if (key_code == LEFT_ARROW)
		data->cam.pos.x += 0.5;
	if (key_code == RIGHT_ARROW)
		data->cam.pos.x -= 0.5;
	if (key_code == UP_ARROW)
		data->cam.pos.z -= 0.5;
	if (key_code == DOWN_ARROW)
		data->cam.pos.z += 0.5;
	ft_camera(data, data->cam.pos, data->cam.to);
	ft_draw(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img_ptr, 0, 0);
	return (0);
}

int			mouse_press(int button, int x, int y, t_data *data)
{
	if (!ft_refresh_image(data))
	{
		ft_lstdel(&data->scene, &ft_del);
		ft_lstdel(&data->light_list, &ft_del);
		exit(1);
	}
	(void)x;
	(void)y;
	if (button == LEFT_CLICK)
		data->cam.pos.y -= 1;
	if (button == RIGHT_CLICK)
		data->cam.pos.y += 1;
	ft_camera(data, data->cam.pos, data->cam.to);
	ft_draw(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img_ptr, 0, 0);
	return (0);
}
