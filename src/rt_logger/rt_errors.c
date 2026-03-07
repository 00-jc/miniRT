/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 15:47:19 by jaicastr          #+#    #+#             */
/*   Updated: 2026/03/07 02:20:10 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_logger/rt_errors.h"
#include "io.h"

__attribute__((__nonnull__(1)))
void	rt_error(const char *s, ...)
{
	va_list	args;

	va_start(args, s);
	ft_vfprintf(STDERR_FILENO, s, args);
	va_end(args);
}
