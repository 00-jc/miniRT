/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_init_aos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 17:24:20 by jaicastr          #+#    #+#             */
/*   Updated: 2026/03/08 01:15:36 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_parser/rt_parser.h"

__attribute__((__always_inline__))
inline t_taggedresult	rt_init_aos(t_vec aos[4])
{
	aos[RT_AOS_SPHERE] = ft_vec_new(16, sizeof(t_RTSphere));
	if (!aos[RT_AOS_SPHERE].head)
		return (KO);
	aos[RT_AOS_LIGHT] = ft_vec_new(16, sizeof(t_RTLight));
	if (!aos[RT_AOS_LIGHT].head)
		return (ft_vec_free(aos), KO);
	aos[2] = ft_vec_new(16, sizeof(t_RTPlane));
	if (!aos[RT_AOS_PLANE].head)
		return (ft_vec_free(aos), ft_vec_free(&aos[RT_AOS_LIGHT]), KO);
	aos[RT_AOS_CYLINDER] = ft_vec_new(16, sizeof(t_RTCylinder));
	if (!aos[RT_AOS_CYLINDER].head)
		return (ft_vec_free(aos), ft_vec_free(&aos[RT_AOS_LIGHT]),
			ft_vec_free(&aos[RT_AOS_PLANE]), KO);
	return (OK);
}

__attribute__((__always_inline__))
inline void	rt_free_aos(t_vec aos[4])
{
	ft_vec_free(aos);
	ft_vec_free(aos + 1);
	ft_vec_free(aos + 2);
	ft_vec_free(aos + 3);
}
