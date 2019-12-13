/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaou <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 14:43:01 by kdaou             #+#    #+#             */
/*   Updated: 2019/07/24 19:22:54 by kdaou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_get_line(char **str, char **line)
{
	int	i;

	i = 0;
	while ((*str)[i] != '\0' && (*str)[i] != '\n')
		i++;
	*line = ft_strsub(*str, 0, i);
	(void)ft_strcpy(*str, *str + i + 1);
	if (**str == '\0')
		ft_strdel(str);
}

int			get_next_line(int fd, char **line)
{
	ssize_t		ret;
	char		buf[BUFF_SIZE + 1];
	static char	*str;
	char		*tmp;

	if (fd < 0 || BUFF_SIZE <= 0 || !line)
		return (-1);
	str = str == NULL ? ft_strnew(0) : str;
	while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[ret] = '\0';
		tmp = str;
		str = ft_strjoin(str, buf);
		ft_strdel(&tmp);
		if (ft_strchr(str, '\n'))
			break ;
	}
	if (ret < 0)
		return (-1);
	if (ret == 0 && (str == NULL || str[0] == '\0'))
		return (0);
	ft_get_line(&str, line);
	return (1);
}
