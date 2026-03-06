/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_coords.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 23:03:44 by jaicastr          #+#    #+#             */
/*   Updated: 2026/03/06 17:20:45 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_parser/rt_parser.h"
#include "rt_logger/rt_errors.h"
#include "conv.h"

__attribute__((__nonnull__(1)))
t_double_res	rt_parse_double(t_tokenizer *t)
{
	t_token			tok[2];
	double			sign;

	ft_skip_whitespace(t);
	sign = 1;
	if (ft_match_next(t, '-'))
		sign = -1;
	tok[0] = ft_eat_while(t, set_digit);
	if (!tok[0].len)
		return (rt_error(NMC, "digit"), (t_double_res){.res = KO});
	if (!ft_match_next(t, '.'))
	{
		ft_skip_whitespace(t);
		return ((t_double_res){.res = OK,
			.d = ft_atod_bounded((char *)tok[0].mem,
				tok[0].len) * sign});
	}
	tok[1] = ft_eat_while(t, set_digit);
	if (!tok[1].len)
		return (rt_error(NMC, "digit"), (t_double_res){.res = KO});
	ft_skip_whitespace(t);
	return ((t_double_res){.res = OK,
		.d = ft_atod_bounded((char *)tok[0].mem,
			tok[0].len + tok[1].len + 1) * sign});
}

__attribute__((__nonnull__(1)))
t_coord_result	rt_parse_coords(t_tokenizer *t)
{
	t_double_res		tmp;
	t_3dcoords			result;

	result = (t_3dcoords){0};
	tmp = rt_parse_double(t);
	if (tmp.res == KO)
		return ((t_coord_result){.res = KO});
	result.x = tmp.d;
	if (!ft_match_next(t, ','))
		return (rt_error(EXP, ',', t->mem[t->cc]),
			(t_coord_result){.res = KO});
	tmp = rt_parse_double(t);
	if (tmp.res == KO)
		return ((t_coord_result){.res = KO});
	result.y = tmp.d;
	if (!ft_match_next(t, ','))
		return (rt_error(EXP, ',', t->mem[t->cc]),
			(t_coord_result){.res = KO});
	tmp = rt_parse_double(t);
	if (tmp.res == KO)
		return ((t_coord_result){.res = KO});
	result.z = tmp.d;
	return ((t_coord_result){.res = OK, .coord = result});
}
