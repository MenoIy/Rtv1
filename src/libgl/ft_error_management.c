/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_management.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaou <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 08:08:09 by kdaou             #+#    #+#             */
/*   Updated: 2019/07/25 08:49:10 by kdaou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgl.h"

void		ft_del(void *content, size_t size)
{
	(void)size;
	free(content);
}

char		*ft_error_type(int error)
{
	char *str[11];

	str[0] = "Error invalid config file";
	str[1] = "Config file syntax error in : Camera";
	str[2] = "Config file syntax error in : Sphere";
	str[3] = "Config file syntax error in : Plane";
	str[4] = "Config file syntax error in : Cone";
	str[5] = "Config file syntax error in : Cylinder";
	str[6] = "Config file syntax error in : Light";
	str[7] = "Error no camera";
	str[8] = "Error 1 camera max";
	str[9] = "Error 1 object at least";
	str[10] = "Error allocating memory";
	return (str[error]);
}

static char	*ft_usage_type(int error)
{
	char *str[8];

	str[0] = "usage : \n./RTv1 config file";
	str[1] = "usage : \n=>camera\n{\n\tposition x y z\n\tlook_at x y z\n}";
	str[2] = "usage : \n=>sphere\n{\n\tradius value\n\tcenter x y z\n\tcolor"
	" r g b\n\tdiffuse r g b\n\tspecular value\n\ttransfo"
	"(optional) 1 2 3 4 | 5 6 7 8 | 9 10 11 12 | 13 14 15 16 \n}";
	str[3] = "usage : \n=>plane\n{\n\tposition x y z\n\tnormal x y z\n\tcolor"
	" r g b\n\tdiffuse r g b\n\tspecular value\n\ttransfo (optional) "
	"1 2 3 4 | 5 6 7 8 | 9 10 11 12 | 13 14 15 16\n}";
	str[4] = "usage : \n=>cone\n{\n\tangle value\n\tcenter x y z\n\tnormal "
	"x y z\n\tcolor r g b\n\tdiffuse r g b\n\tspecular value\n\ttransfo "
	"(optional) 1 2 3 4 | 5 6 7 8 | 9 10 11 12 | 13 14 15 16\n}";
	str[5] = "usage : \n=>cylinder\n{\n\tradius value\n\tcenter x y z\n\t"
	"normal x y z\n\tcolor r g b\n\tdiffuse r g b\n\tspecular value\n\ttransfo "
	"(optional) 1 2 3 4 | 5 6 7 8 | 9 10 11 12 | 13 14 15 16\n}";
	str[6] = "usage : \n=>light\n{\n\tposition x y z\n\tintensity r g b\n}";
	str[7] = "usage : \n=>camera\n{\n\tposition x y z\n\tlook_at x y z\n}";
	return (str[error]);
}

void		ft_error_management(t_data *data, int error, void **to_free, int fd)
{
	if (fd != -1)
		close(fd);
	ft_memdel(to_free);
	ft_putendl_fd(ft_error_type(error), 2);
	if (error <= 7)
		ft_putendl_fd(ft_usage_type(error), 2);
	ft_lstdel(&data->scene, &ft_del);
	ft_lstdel(&data->light_list, &ft_del);
	exit(1);
}
