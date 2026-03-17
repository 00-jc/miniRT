/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parse_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 19:10:37 by jaicastr          #+#    #+#             */
/*   Updated: 2026/03/17 03:29:27 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_parser/rt_parser.h"
#include "io.h"

__attribute__((__always_inline__, __nonnull__(1, 2)))
inline t_RTTexture *rt_parse_path(t_RTContext *ctx, t_tokenizer *t)
{
	t_tokenizer		snap;
	t_token			tok;
	t_RTTexture		*tx;

	snap = *t;
	ft_skip_whitespace(t);
	tok = ft_eat_until(t, set_blank);
	tx = rt_parse_bmp(ctx, tok);
	if (!tx)
		*t = snap;
	return (tx);
}
