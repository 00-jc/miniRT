/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_errors.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 15:45:52 by jaicastr          #+#    #+#             */
/*   Updated: 2026/03/10 15:26:15 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_ERRORS_H
# define RT_ERRORS_H

# include <stddef.h>
# include <stdarg.h>

void	rt_error(const char *s, ...)\
			__attribute__((__nonnull__(1)));

# define OOR	"Error\nOUT-OF-RANGE value 0x%lX for values [0x%lX -> 0x%lX]\n"
# define OORD	"Error\nOUT-OF-RANGE value %f for values [%f -> %f]\n"
# define NMC	"Error\nParser cannot match sequence of: '%s'\n"
# define EXP	"Error\nExpected 0x%x got: 0x%x\n"
# define NNORM	"Error\nAxis should be normalized\n"
# define NBRI	"Error\nBrightess should be normalized\n"
# define REDEF	"Error\n%s should not be redefined\n"
# define UNREC	"Error\nUnrecognised label\n"
# define SOA	"Error\nCannot migrate from AoS -> Soa\n"
# define USAGE	"Error\n%s <file>.rt <width> <height>\n"
# define DISPL	"Error\nInvalid display parameters\n"

# define NDIAM	"Error\nNegative diameter is not physically possible for a \
sphere\n"
# define NDEF	"Error\nYou have to define at least a camera and an am\
bient light"

#endif
