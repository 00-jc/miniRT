/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_print_light.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoria <asoria@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 19:44:05 by asoria            #+#    #+#             */
/*   Updated: 2026/03/07 21:03:03 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_logger/rt_printer.h"

__attribute__((__nonnull__(1), __always_inline__))
inline void	rt_print_light(t_RTLight *light)
{
	ft_printf("Object: Light\n");
	ft_printf("\tcoords: %f, :%f, %f\n", light->coords,
		light->coords, light->coords);
	ft_printf("\tbrighthness: %f\n", light->brightness);
	ft_printf("\tcolor: %x\n", light->color);
}

__attribute__((__nonnull__(1), __always_inline__))
inline void	rt_print_ambient(t_RTAmbientLight *light)
{
	ft_printf("Object: Ambient Light\n");
	ft_printf("\tbrightness: %f\n", light->brightness);
	ft_printf("\tcolor: %x\n", light->color);
	ft_printf("\tinitializacion: %d\n", light->is_init);
}
