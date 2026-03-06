/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_errors.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 15:45:52 by jaicastr          #+#    #+#             */
/*   Updated: 2026/03/06 15:55:43 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_ERRORS_H
# define RT_ERRORS_H

# include <stddef.h>
# include <stdarg.h>

void	rt_error(const char *s, ...)\
			__attribute__((__nonnull__(1)));

#define OOR "ERROR\nOUT-OF-RANGE value %lX for values [%lX->%lX]\n"
#define NMC "ERROR\nParser cannot match sequence of: '%s'\n"
#define EXP "ERROR\nExpected '%x' got: '%x'\n"

#endif
