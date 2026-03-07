/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_errors.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 15:45:52 by jaicastr          #+#    #+#             */
/*   Updated: 2026/03/07 02:50:45 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_ERRORS_H
# define RT_ERRORS_H

# include <stddef.h>
# include <stdarg.h>

void	rt_error(const char *s, ...)\
			__attribute__((__nonnull__(1)));

# define OOR "ERROR\nOUT-OF-RANGE value 0x%lX for values [0x%lX -> 0x%lX]\n"
# define NMC "ERROR\nParser cannot match sequence of: '%s'\n"
# define EXP "ERROR\nExpected 0x%x got: 0x%x\n"
# define NDIAM "ERROR\nNegative diameter is not physically possible for a \
sphere\n"
# define NNORM "ERROR\nAxis should be normalized\n"
# define NBRI "ERROR\nBrightess should be normalized\n"

#endif
