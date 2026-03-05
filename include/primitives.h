/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   primitives.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 18:51:09 by jaicastr          #+#    #+#             */
/*   Updated: 2026/03/04 21:34:57 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRIMITIVES_H
# define PRIMITIVES_H

# include "math.h"

/* 
 * Holds 4 doubles packed and aligned to 64.
 * we add one more field so it can fit in a whole avx* register.
 */

typedef t_4packd	t_3dcoords;

#endif
