/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_printer.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 20:56:10 by jaicastr          #+#    #+#             */
/*   Updated: 2026/03/07 21:14:56 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_PRINTER_H
# define RT_PRINTER_H

# include "io.h"
# include "rt_miniRT.h"

void	rt_print_cylinder(t_RTCylinder *cylinder)\
			__attribute__((__nonnull__(1)));

void	rt_print_plane(t_RTPlane *plane)\
			__attribute__((__nonnull__(1)));

void	rt_print_sphere(t_RTSphere *sphere)\
			__attribute__((__nonnull__(1)));

void	rt_print_light(t_RTLight *light)\
			__attribute__((__nonnull__(1)));

void	rt_print_ambient(t_RTAmbientLight *light)\
			__attribute__((__nonnull__(1)));

void	rt_print_camera(t_RTCamera *cam)\
			__attribute__((__nonnull__(1)));

#endif
