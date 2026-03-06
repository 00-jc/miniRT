/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 23:03:44 by jaicastr          #+#    #+#             */
/*   Updated: 2026/03/06 03:04:30 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_parser/parser.h"
#include "conv.h"

__attribute__((__nonnull__(1)))
t_unsigned_res	rt_parse_usigned(t_tokenizer *t)
{
	t_token			tok;
	size_t			n;

	ft_skip_whitespace(t);
	tok = ft_eat_while(t, set_digit);
	if (!tok.len)
		return ((t_unsigned_res){.res = KO});
	n = ft_atoul_bounded((char *)tok.mem, tok.len);
	if (n > UINT8_MAX)
		return ((t_unsigned_res){.res = KO});
	ft_skip_whitespace(t);
	return ((t_unsigned_res){.res = OK, .u = n});
}

__attribute__((__nonnull__(1)))
t_color_result	rt_parse_color(t_tokenizer *t)
{
	t_unsigned_res		tmp;
	t_u32a				color;

	color = 0;
	tmp = rt_parse_usigned(t);
	if (tmp.res == KO)
		return ((t_color_result){.res = KO});
	color |= (tmp.u << 16);
	if (!ft_match_next(t, ','))
		return ((t_color_result){.res = KO});
	tmp = rt_parse_usigned(t);
	if (tmp.res == KO)
		return ((t_color_result){.res = KO});
	color |= (tmp.u << 8);
	if (!ft_match_next(t, ','))
		return ((t_color_result){.res = KO});
	tmp = rt_parse_usigned(t);
	if (tmp.res == KO)
		return ((t_color_result){.res = KO});
	color |= tmp.u;
	return ((t_color_result){.res = OK, .color = color});
}
