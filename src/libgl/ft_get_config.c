/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_config.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaou <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 08:26:04 by kdaou             #+#    #+#             */
/*   Updated: 2019/07/24 19:08:16 by kdaou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgl.h"

const t_function g_t_function[6] =
{
	{ "=>camera :", &ft_get_camera_config },
	{ "=>light :", &ft_get_light_config },
	{ "=>sphere :", &ft_get_sphere_config },
	{ "=>plane :", &ft_get_plane_config },
	{ "=>cone :", &ft_get_cone_config },
	{ "=>cylinder :", &ft_get_cylinder_config }
};

void	ft_get_config(char *conf_file, t_data *data)
{
	int		fd;
	char	*line;
	int		i;

	data->cam.n = 0;
	fd = open(conf_file, O_RDONLY);
	if (fd < 0)
		ft_error_management(data, 0, NULL, fd);
	while (get_next_line(fd, &line) > 0)
	{
		i = 0;
		while (i < (int)STATIC_ARRAY_SIZE(g_t_function))
		{
			if (!ft_strcmp(g_t_function[i].type, line))
			{
				ft_strdel(&line);
				g_t_function[i].call(fd, data);
				break ;
			}
			i++;
		}
		ft_strdel(&line);
	}
	close(fd);
	ft_cheak_data(data);
}
