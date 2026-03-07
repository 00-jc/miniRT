/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_print_light.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoria <asoria@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 19:44:05 by asoria            #+#    #+#             */
/*   Updated: 2026/03/07 20:08:02 by asoria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

__attribute__((__always_inline__))
inline void	rt_print_light(t_RTLight light)
{
	ft_printf("Object: Light\n");
	ft_printf("\tcoords: %f, :%f, %f\n", light.coords.coord.x,
		light.coords.coord.y, light.coords.coord.z);
	ft_printf("\tbrighthness: %f\n", light.brightness);
	ft_printf("\tcolor: %x\n", light.color);
}

__attribute__((__always_inline__))
inline void	rt_print_ambient(t_RTAmbientLight light)
{
	ft_printf("Object: Ambient Light\n");
	ft_printf("\tbrightness: %f\n", light.brightness);
	ft_printf("\tcolor: %x\n", light.color);
	ft_printf("\tinitializacion: %d\n", light.is_init);
}
