/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_init_aos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 17:24:20 by jaicastr          #+#    #+#             */
/*   Updated: 2026/03/07 20:15:27 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_parser/rt_parser.h"

__attribute__((__always_inline__))
inline t_taggedresult	rt_init_aos(t_vec aos[4])
{
	aos[0] = ft_vec_new(16, sizeof(t_RTSphere));
	if (!aos[0].head)
		return (KO);
	aos[1] = ft_vec_new(16, sizeof(t_RTLight));
	if (!aos[1].head)
		return (ft_vec_free(aos), KO);
	aos[2] = ft_vec_new(16, sizeof(t_RTPlane));
	if (!aos[2].head)
		return (ft_vec_free(aos), ft_vec_free(&aos[1]), KO);
	aos[3] = ft_vec_new(16, sizeof(t_RTCylinder));
	if (!aos[3].head)
		return (ft_vec_free(aos), ft_vec_free(&aos[1]),
			ft_vec_free(&aos[2]), KO);
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
