/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_camera.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 18:27:41 by jaicastr          #+#    #+#             */
/*   Updated: 2026/03/14 01:30:03 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_CAMERA_H
# define RT_CAMERA_H

# include "math.h"

typedef struct s_RTCamera
{
	t_3dcoords	coords;
	t_3dcoords	axis;
	t_u8		fov;
	t_u8		is_init;
	double		yaw;
	double		pitch;
}	t_RTCamera;

#endif
