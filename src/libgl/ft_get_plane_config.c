/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_plane_config.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaou <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 13:31:36 by kdaou             #+#    #+#             */
/*   Updated: 2019/07/24 19:15:29 by kdaou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgl.h"

static int	ft_stock_plane_config_transfo(char *line, t_plane *p)
{
	int j;

	j = 0;
	if (ft_expect_matrix(line, "\ttransfo ", &(p->normal)))
	{
		p->normal = ft_vec4_normalize(p->normal);
		j++;
	}
	if (ft_expect_matrix(line, "\ttransfo ", &(p->point)))
		j++;
	return (j == 2 ? 1 : 0);
}

static int	ft_stock_plane_config(int fd, t_plane *p, int i, int j)
{
	char	*s;

	s = NULL;
	while (get_next_line(fd, &s) > 0)
	{
		if (!(i & 1) && ft_expect_vector(s, "\tposition", &(p->point)))
			i += 1;
		else if (!(i & 2) && ft_expect_color(s, "\tcolor", &(p->color)))
			i += 2;
		else if (!(i & 4) && ft_expect_diffuse(s, "\tdiffuse", &(p->diffuse)))
			i += 4;
		else if (!(i & 8) && ft_expect_value(s, "\tspecular", &(p->specular)))
			i += 8;
		else if (!(i & 16) && ft_expect_vector(s, "\tnormal", &(p->normal)))
			i += 16;
		else if (!(i & 32) && ft_stock_plane_config_transfo(s, p))
			i += 32;
		else if ((j = ft_bracket_control(s, '}')))
			break ;
		else
			break ;
		ft_strdel(&s);
	}
	ft_strdel(&s);
	return ((i == 31 || i == 63) && j ? 1 : 0);
}

void		ft_get_plane_config(int fd, t_data *data)
{
	char	*line;
	t_plane	*plane;

	if (!(plane = (t_plane *)malloc(sizeof(t_plane))))
		ft_error_management(data, 10, NULL, fd);
	while (get_next_line(fd, &line) > 0)
	{
		if (ft_bracket_control(line, '{'))
		{
			if (!(ft_stock_plane_config(fd, plane, 0, 0)))
			{
				ft_memdel((void **)&plane);
				ft_error_management(data, 3, (void **)&line, fd);
			}
			else
			{
				ft_strdel(&line);
				break ;
			}
		}
		else
			ft_error_management(data, 3, (void **)&line, fd);
	}
	plane->normal = ft_vec4_normalize(plane->normal);
	ft_lstadd(&(data->scene), ft_lstnew((void *)plane, PLANE));
}
