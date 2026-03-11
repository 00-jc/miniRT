/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parse_display_size.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 15:24:18 by jaicastr          #+#    #+#             */
/*   Updated: 2026/03/11 01:53:57 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_parser/rt_parser.h"
#include "rt_logger/rt_errors.h"
#include "cstr.h"
#include "conv.h"

__attribute__((__always_inline__, __nonnull__(2, 3, 4)))
inline t_taggedresult	rt_parse_display_size(int argc, t_RTContext *context,
	const char *width, const char *height)
{
	t_tokenizer		t;
	t_token			token;

	if (argc < 4)
		return ((void)(context->display_width = 1280),
				(void)(context->display_height = 720), OK);
	if (!*width || !*height)
		return (KO);
	t = ft_tokenizer_over((void *)width, ft_strlen(width));
	token = ft_eat_while(&t, set_digit);
	if (!token.len)
		return (rt_error(DISPL), KO);
	context->display_width = ft_atoul_bounded((char *)token.mem, token.len);
	if (t.cc != t.max)
		return (rt_error(DISPL), KO);
	t = ft_tokenizer_over((void *)height, ft_strlen(width));
	token = ft_eat_while(&t, set_digit);
	if (!token.len)
		return (rt_error(DISPL), KO);
	context->display_height = ft_atoul_bounded((char *)token.mem, token.len);
	if (t.cc != t.max)
		return (rt_error(DISPL), KO);
	return (OK);
}
