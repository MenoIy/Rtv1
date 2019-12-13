/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_light_intersection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 15:23:03 by msidqi            #+#    #+#             */
/*   Updated: 2019/07/24 18:12:36 by kdaou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgl.h"

static double	ft_specular(t_ray *ray, double dot_prod,
									t_vec4 normal, t_vec4 vec_to_light)
{
	t_vec4	v;
	t_vec4	r;

	if (dot_prod == 0)
		return (0);
	v = ft_vec4_scalar(ray->dir, -1);
	r = ft_vec4_sub(ft_vec4_scalar(normal, 2 * dot_prod), vec_to_light);
	return (pow(ft_min(ft_vec4_dot_product(r, v), 0), SPECULAR_POW));
}

static void		ft_diffuse(t_shader_x *shx, double dot_prod,
		t_vec4 *ds, t_light *li)
{
	shx->diff.x += dot_prod * ds[0].x * li->i_r;
	shx->diff.y += dot_prod * ds[0].y * li->i_g;
	shx->diff.z += dot_prod * ds[0].z * li->i_b;
}

unsigned int	ft_compute_shader(unsigned int color, t_shader_x *sh_x)
{
	t_shader shader;

	shader.specular = ft_color_rgb_scalar(0xFFFFFF,
			sh_x->spec.x, sh_x->spec.y, sh_x->spec.z);
	shader.diffuse = ft_color_rgb_scalar(color,
			sh_x->diff.x, sh_x->diff.y, sh_x->diff.z);
	shader.ambient = ft_color_rgb_scalar(color,
			AMBIENT_R, AMBIENT_G, AMBIENT_B);
	return (ft_color_add(shader.specular,
						ft_color_add(shader.diffuse, shader.ambient)));
}

static const	t_obj_function g_t_obj_functions[4] =
{
	{SPHERE, &ft_sphere_inter, &ft_sphere_shader},
	{PLANE, &ft_plane_inter, &ft_plane_shader},
	{CONE, &ft_cone_inter, &ft_cone_shader},
	{CYLINDER, &ft_cylinder_inter, &ft_cylinder_shader}
};

/*
** 3-loop to see if ray is blocked by any another
** 							object in scene, towards light source.
*/

int				ft_ray_inter_objs(t_list *list, t_ray *r_light,
		double distance_to_light)
{
	t_list			*scene;
	unsigned int	i;

	scene = list;
	while (scene != NULL)
	{
		r_light->t = FAR;
		i = -1;
		while (++i < (unsigned int)STATIC_ARRAY_SIZE(g_t_obj_functions))
		{
			if (g_t_obj_functions[i].type == scene->content_size &&
					g_t_obj_functions[i].call(r_light, scene->content) &&
					distance_to_light > ft_vec4_mag(ft_vec4_scalar(r_light->dir,
							r_light->t)))
				return (1);
		}
		scene = scene->next;
	}
	return (0);
}

/*
** rl : ray_to_light
** dp : dot_product
** ds diffuse && specular
** send ray to light
** loop through all lights
** if ray reached light, add value to shader
*/

t_shader_x		ft_ray_inter_lights(t_data *data,
										t_vec4 nr, t_ray *ray, t_vec4 *ds)
{
	t_ray			rl;
	t_shader_x		shx;
	t_list			*l;
	double			dp;
	t_light			*li;

	l = data->light_list;
	shx.diff = ft_create_vec4(0.0, 0.0, 0.0, 0.0);
	shx.spec = ft_create_vec4(0.0, 0.0, 0.0, 0.0);
	while (l)
	{
		li = l->content;
		rl = ft_get_ray_to_light(ray, l->content);
		dp = ft_min(ft_vec4_dot_product(rl.dir, nr), 0);
		if (!ft_ray_inter_objs(data->scene, &rl,
					ft_vec4_mag(ft_vec4_sub(li->origin, rl.origin))))
		{
			ft_diffuse(&shx, dp, ds, li);
			shx.spec.x += ft_specular(ray, dp, nr, rl.dir) * ds[1].x * li->i_r;
			shx.spec.y += ft_specular(ray, dp, nr, rl.dir) * ds[1].y * li->i_g;
			shx.spec.z += ft_specular(ray, dp, nr, rl.dir) * ds[1].z * li->i_b;
		}
		l = l->next;
	}
	return (shx);
}
