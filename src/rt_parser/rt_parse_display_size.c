/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parse_display_size.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 15:24:18 by jaicastr          #+#    #+#             */
/*   Updated: 2026/03/11 00:29:34 by asoria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_parser/rt_parser.h"
#include "rt_logger/rt_errors.h"
#include "cstr.h"
#include "conv.h"

__attribute__((__always_inline__, __nonnull__(1, 2, 3)))
inline t_taggedresult	rt_parse_display_size(t_RTContext *context,
	const char *width, const char *height)
{
	t_tokenizer		t;
	t_token			token;

	if (!*width || !*height)
	{	
		context->display_width = 1280;
		context->display_height = 720;
		return (OK);
	}
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
