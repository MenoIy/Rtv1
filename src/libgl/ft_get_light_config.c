/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_light_config.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaou <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 13:01:45 by kdaou             #+#    #+#             */
/*   Updated: 2019/07/24 19:12:22 by kdaou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgl.h"

static int	ft_stock_light_config(int fd, t_light *l, int i, int j)
{
	char	*s;

	s = NULL;
	while (get_next_line(fd, &s) > 0)
	{
		if (ft_expect_vector(s, "\tposition", &(l->origin)))
			i += 1;
		else if (ft_expect_intensity(s, "\tintensity", l))
			i -= 2;
		else if ((j = ft_bracket_control(s, '}')))
			break ;
		else
			break ;
		ft_strdel(&s);
	}
	ft_strdel(&s);
	return (i == -1 && j ? 1 : 0);
}

void		ft_get_light_config(int fd, t_data *data)
{
	char	*line;
	t_light	*light;

	if (!(light = (t_light *)malloc(sizeof(t_light))))
		return ;
	while (get_next_line(fd, &line) > 0)
	{
		if (ft_bracket_control(line, '{'))
		{
			if (!(ft_stock_light_config(fd, light, 0, 0)))
			{
				ft_memdel((void **)&light);
				ft_error_management(data, 6, (void **)&line, fd);
			}
			else
			{
				ft_strdel(&line);
				break ;
			}
		}
		else
			ft_error_management(data, 6, (void **)&line, fd);
	}
	ft_lstadd(&(data->light_list), ft_lstnew((void *)light, 0));
}
