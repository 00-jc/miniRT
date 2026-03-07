/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_print_cylinder.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoria <asoria@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 19:44:11 by asoria            #+#    #+#             */
/*   Updated: 2026/03/07 20:07:04 by asoria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

__attributes__((__always_inline__))
inline void	rt_print_cylinder(t_RTCylinder cylinder)
{
	ft_printf("Object: Cylinder\n");
	ft_printf("\tcoords: %f, %f, %f\n", cylinder.coords.coord.x,
		cylinder.coords.coord.y, cylinder.coords.coord.z);
	ft_printf("\taxis: %f, %f, %f\n", cylinder.axis.coord.x,
		cylinder.axis.coord.y, cylinder.axis.coord.z);
	ft_printf("\twidth/height: %f, %f", cylinder.wh.w, cylinder.wh.h);
	ft_printf("\tcolor: %x", cylinder.color);
}
