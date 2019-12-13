/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 12:48:35 by msidqi            #+#    #+#             */
/*   Updated: 2019/07/24 20:23:46 by kdaou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libgl.h"

int		main(int argc, char **argv)
{
	t_data	data;

	data.light_list = NULL;
	data.scene = NULL;
	data.cam.absolute_up = ft_create_vec4(0, 1, 0, 0);
	data.cam.focal_length = 2;
	if (argc != 2)
	{
		ft_putendl_fd("Invalid number of config file\n"
		"usage : \n./RTv1 config file", 2);
		return (1);
	}
	ft_get_config(argv[1], &data);
	if (!ft_window_setup(&data, "ReTweet", HEIGHT, WIDTH)
													|| !ft_image_setup(&data))
		ft_error_management(&data, 10, NULL, -1);
	ft_camera(&data, data.cam.pos, data.cam.to);
	ft_draw(&data);
	mlx_put_image_to_window(data.mlx, data.win, data.img_ptr, 0, 0);
	ft_mlx_hooks(&data, RED_BUTTON_HOOK | KEY_PRESS_HOOK | MOUSE_PRESS_HOOK);
	mlx_loop(data.mlx);
	return (0);
}

/*
**	macro up : 1;
**	macro down  : 2;
**	macro left : 4;
**	macro right  : 8;
**	(left | up | left | right)
**
** Vec P(x,y,z,w) , Vec C(5,5,5,1)
**
** |P - C|² = r²
** 	P - C² 	= r²
**
** magnitude A =  ||A|| = P-C
** magnitude B =  ||B|| = V = 1
**
** B is normalazed
**
** angle  entre (vec4 A et vec4 B)  ==    dotprod(A , B)
**
** dot(A, B )  =   cos (A , B) * ||A||  * ||1||
** cos (A , B) =   dot(A, B )  / ||A||  * ||1||
*/
