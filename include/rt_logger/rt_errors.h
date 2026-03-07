/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_errors.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 15:45:52 by jaicastr          #+#    #+#             */
/*   Updated: 2026/03/07 04:34:59 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_ERRORS_H
# define RT_ERRORS_H

# include <stddef.h>
# include <stdarg.h>

void	rt_error(const char *s, ...)\
			__attribute__((__nonnull__(1)));

# define OOR "Error\nOUT-OF-RANGE value 0x%lX for values [0x%lX -> 0x%lX]\n"
# define OORD "Error\nOUT-OF-RANGE value %f for values [%f -> %f]\n"
# define NMC "Error\nParser cannot match sequence of: '%s'\n"
# define EXP "Error\nExpected 0x%x got: 0x%x\n"
# define NDIAM "Error\nNegative diameter is not physically possible for a \
sphere\n"
# define NNORM "Error\nAxis should be normalized\n"
# define NBRI "Error\nBrightess should be normalized\n"
# define REDEF "Error\n%s should be redefined\n"

#endif
