/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_operations.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 16:29:15 by msidqi            #+#    #+#             */
/*   Updated: 2019/06/18 16:29:16 by msidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgl.h"

void		ft_putmatrix(t_matrix *mat)
{
	unsigned int	i;
	unsigned int	j;

	i = -1;
	write(1, "\n", 1);
	while (++i < mat->rows)
	{
		j = -1;
		while (++j < mat->cols)
		{
			if (j == mat->cols - 1)
			{
				ft_putnbr(mat->v[i][j]);
				write(1, " |\n", 3);
			}
			else
			{
				ft_putnbr(mat->v[i][j]);
				write(1, " ", 1);
			}
		}
	}
	write(1, "\n", 1);
}

void		ft_putvec4(t_vec4 *vec)
{
	write(1, "Vector( ", 8);
	ft_putnbr(vec->x);
	write(1, ", ", 2);
	ft_putnbr(vec->y);
	write(1, ", ", 2);
	ft_putnbr(vec->z);
	write(1, ", ", 2);
	ft_putnbr(vec->w);
	write(1, " )\n", 3);
}

void		ft_printvec4(t_vec4 *vec)
{
	printf("Vector(%f, %f, %f, %f)\n", vec->x, vec->y, vec->z, vec->w);
}

void		ft_printmatrix4(t_matrix4 *mat)
{
	unsigned int	i;
	unsigned int	j;

	i = -1;
	write(1, "\n", 1);
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
		{
			if (j == 3)
				printf("% .2f|\n", mat->v[i][j]);
			else
				printf("% .2f ", mat->v[i][j]);
		}
	}
	write(1, "\n", 1);
}

void		ft_putmatrix4(t_matrix4 *mat)
{
	unsigned int	i;
	unsigned int	j;

	i = -1;
	write(1, "\n", 1);
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
		{
			if (j == 3)
			{
				ft_putnbr(mat->v[i][j]);
				write(1, " |\n", 3);
			}
			else
			{
				ft_putnbr(mat->v[i][j]);
				write(1, " ", 1);
			}
		}
	}
	write(1, "\n", 1);
}
