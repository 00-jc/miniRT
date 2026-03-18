/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_aos_to_soa.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoria <asoria@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 01:35:34 by asoria            #+#    #+#             */
/*   Updated: 2026/03/18 16:34:01 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_parser/rt_parser.h"

__attribute__((__always_inline__, __nonnull__(1, 2, 3)))
inline t_taggedresult	rt_aos_to_soa(t_vec aos[5],
		t_RTScene *scene, t_arena *arena)
{
	if (rt_aos_to_soa_sphere(&scene->rt_sphere_buffer,
			&aos[RT_AOS_SPHERE], arena) == KO
		|| rt_aos_to_soa_light(&scene->rt_light_buffer,
			&aos[RT_AOS_LIGHT], arena) == KO
		|| rt_aos_to_soa_cylinder(&scene->rt_cylinder_buffer,
			&aos[RT_AOS_CYLINDER], arena) == KO
		|| rt_aos_to_soa_plane(&scene->rt_plane_buffer,
			&aos[RT_AOS_PLANE], arena) == KO
		|| rt_aos_to_soa_cone(&scene->rt_cone_buffer,
			&aos[RT_AOS_CONE], arena) == KO)
		return (KO);
	return (OK);
}
