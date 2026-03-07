/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_print_plane.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoria <asoria@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 20:05:52 by asoria            #+#    #+#             */
/*   Updated: 2026/03/07 20:12:23 by asoria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

__attribute__((__always_inline__))
inline void	rt_print_plane(t_RTPlane plane)
{
	ft_printf("Object: Plane\n");
	ft_printf("\tcoords: %f, %f, %f\n", plane.coords.coord.x,
		plane.coords.coord.y, plane.coords.coord.z);
	ft_printf("\taxis: %f, %f, %f\n", plane.axis.coord.x,
		plane.axis.coord.y, plane.axis.coord.z);
	ft_printf("\tcolor: %x\n", plane.color);
}
