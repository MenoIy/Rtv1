/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_cone_config.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaou <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 14:36:25 by kdaou             #+#    #+#             */
/*   Updated: 2019/07/24 19:25:44 by kdaou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgl.h"

static int	ft_stock_cone_config_next(char *line, t_cone *p, int *i)
{
	int	j;
	int	tmp;

	j = 0;
	tmp = 0;
	if (!(*i & 32) && ft_expect_value(line, "\tangle", &(p->half_angle)))
	{
		tmp = 1;
		*i += 32;
	}
	if (ft_expect_matrix(line, "\ttransfo ", &(p->axis)))
	{
		p->axis = ft_vec4_normalize(p->axis);
		j++;
	}
	if (ft_expect_matrix(line, "\ttransfo ", &(p->center)))
		j++;
	if (j == 2)
		*i += 64;
	return (j == 2 || tmp ? 1 : 0);
}

static int	ft_stock_cone_config(int fd, t_cone *p, int i, int j)
{
	char	*s;

	s = NULL;
	while (get_next_line(fd, &s) > 0)
	{
		if (!(i & 1) && ft_expect_vector(s, "\tcenter", &(p->center)))
			i += 1;
		else if (!(i & 2) && ft_expect_color(s, "\tcolor", &(p->color)))
			i += 2;
		else if (!(i & 4) && ft_expect_diffuse(s, "\tdiffuse", &(p->diffuse)))
			i += 4;
		else if (!(i & 8) && ft_expect_value(s, "\tspecular", &(p->specular)))
			i += 8;
		else if (!(i & 16) && ft_expect_vector(s, "\tnormal", &(p->axis)))
			i += 16;
		else if (!(i & 64) && ft_stock_cone_config_next(s, p, &i))
			i += 0;
		else if ((j = ft_bracket_control(s, '}')))
			break ;
		else
			break ;
		ft_strdel(&s);
	}
	ft_strdel(&s);
	return ((i == 63 || i == 127) && j ? 1 : 0);
}

void		ft_get_cone_config(int fd, t_data *data)
{
	char	*line;
	t_cone	*cone;

	if (!(cone = (t_cone *)malloc(sizeof(t_cone))))
		ft_error_management(data, 10, NULL, fd);
	while (get_next_line(fd, &line) > 0)
	{
		if (ft_bracket_control(line, '{'))
		{
			if (!(ft_stock_cone_config(fd, cone, 0, 0)))
			{
				ft_memdel((void **)&cone);
				ft_error_management(data, 4, (void **)&line, fd);
			}
			else
			{
				ft_strdel(&line);
				break ;
			}
		}
		else
			ft_error_management(data, 4, (void **)&line, fd);
	}
	cone->axis = ft_vec4_normalize(cone->axis);
	ft_lstadd(&(data->scene), ft_lstnew((void *)cone, CONE));
}
