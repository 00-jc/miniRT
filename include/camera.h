/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 18:27:41 by jaicastr          #+#    #+#             */
/*   Updated: 2026/03/04 21:35:20 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# include "primitives.h"

typedef struct s_RTCamera
{
	t_3dcoords	coords;
	t_3dcoords	axis;
	t_u8		fov;
}	t_RTCamera;

#endif
