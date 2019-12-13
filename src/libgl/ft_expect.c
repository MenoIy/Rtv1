/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaou <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 08:03:33 by kdaou             #+#    #+#             */
/*   Updated: 2019/07/25 09:16:02 by kdaou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgl.h"

int	ft_expect_vector(char *line, char *name, t_vec4 *vector)
{
	char	**tab;
	int		i;

	if (!line)
		return (0);
	if (!(tab = ft_strsplit(line, ' ')))
		return (0);
	if (ft_table_size(tab) != 4 ||
			ft_strcmp(tab[0], name) != 0)
	{
		ft_free_tab(&tab);
		return (0);
	}
	i = 0;
	while (tab[++i])
		if (!ft_is_numeric(tab[i]))
		{
			ft_free_tab(&tab);
			return (0);
		}
	i = !ft_strcmp(tab[0], "\tnormal") ? 0 : 1;
	*vector = ft_create_vec4(ft_atof(tab[1]), ft_atof(tab[2]),
			ft_atof(tab[3]), i);
	ft_free_tab(&tab);
	return (1);
}

int	ft_expect_value(char *line, char *name, double *value)
{
	char	**tab;

	if (!line)
		return (0);
	if (!(tab = ft_strsplit(line, ' ')))
		return (0);
	if (ft_table_size(tab) != 2 || ft_strcmp(tab[0],
				name) != 0)
	{
		ft_free_tab(&tab);
		return (0);
	}
	if (!ft_is_numeric(tab[1]))
	{
		ft_free_tab(&tab);
		return (0);
	}
	if (!ft_strcmp(tab[0], "\tspecular") && !ft_is_limited(ft_atof(tab[1])))
	{
		ft_free_tab(&tab);
		return (0);
	}
	*value = ft_min(ft_atof(tab[1]), 0);
	ft_free_tab(&tab);
	return (1);
}

int	ft_expect_intensity(char *line, char *name, t_light *light)
{
	char	**tab;
	int		i;

	if (!line)
		return (0);
	if (!(tab = ft_strsplit(line, ' ')))
		return (0);
	if (ft_table_size(tab) != 4 ||
			ft_strcmp(tab[0], name) != 0)
	{
		ft_free_tab(&tab);
		return (0);
	}
	i = 0;
	while (tab[++i])
		if (!ft_is_numeric(tab[i]) || !ft_is_limited(ft_atof(tab[i])))
		{
			ft_free_tab(&tab);
			return (0);
		}
	light->i_r = ft_atof(tab[1]);
	light->i_g = ft_atof(tab[2]);
	light->i_b = ft_atof(tab[3]);
	ft_free_tab(&tab);
	return (1);
}

int	ft_expect_diffuse(char *line, char *name, t_vec4 *vector)
{
	char	**tab;
	int		i;

	if (!line)
		return (0);
	if (!(tab = ft_strsplit(line, ' ')))
		return (0);
	if (ft_table_size(tab) != 4 ||
			ft_strcmp(tab[0], name) != 0)
	{
		ft_free_tab(&tab);
		return (0);
	}
	i = 0;
	while (tab[++i])
		if (!ft_is_numeric(tab[i]) || !ft_is_limited(ft_atof(tab[i])))
		{
			ft_free_tab(&tab);
			return (0);
		}
	*vector = ft_create_vec4(ft_atof(tab[1]), ft_atof(tab[2]),
			ft_atof(tab[3]), 0);
	ft_free_tab(&tab);
	return (1);
}

int	ft_expect_color(char *line, char *name, unsigned int *color)
{
	char	**tab;

	if (!line)
		return (0);
	if (!(tab = ft_strsplit(line, ' ')))
		return (0);
	if (ft_table_size(tab) != 4 ||
			ft_strcmp(tab[0], name) != 0)
	{
		ft_free_tab(&tab);
		return (0);
	}
	if (!ft_is_numeric(tab[1]))
	{
		ft_free_tab(&tab);
		return (0);
	}
	*color = ((int)ft_max(ft_min(ft_atof(tab[1]), 0), 255) << 16) |
		((int)ft_max(ft_min(ft_atof(tab[2]), 0), 255) << 8) |
		(int)ft_max(ft_min(ft_atof(tab[3]), 0), 255);
	ft_free_tab(&tab);
	return (1);
}
