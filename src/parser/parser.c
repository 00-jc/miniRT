/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 11:53:01 by jaicastr          #+#    #+#             */
/*   Updated: 2026/03/05 22:45:13 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_parser/parser.h"
#include "io.h"

__attribute__((__nonnull__(1), __always_inline__, hot))
static inline t_token	rt_get_next_label(t_tokenizer *tokenizer)
{
	ft_skip_whitespace(tokenizer);
	return (ft_eat_until(tokenizer, set_blank));
}

__attribute__((__nonnull__(1)))
static inline t_u32a	ft_parse_scene(t_RTScene *scene, t_file file)
{
	t_tokenizer	tokenizer;
	t_token		token;

	(void)scene;
	tokenizer = ft_tokenizer_over(file.content, file.size);
	while (tokenizer.cc != tokenizer.max)
	{
		token = rt_get_next_label(&tokenizer);
		if (!token.len)
			break;
		ft_printf("LABEL: ");
		(void)write(STDOUT_FILENO, token.mem, token.len);
		ft_printf("\n");
		// TODO: process said label
	}
	return (1);
}

__attribute__((__nonnull__(1, 2)))
t_u32a	rt_parse_file_into_state(t_RTScene *scene, char *fname)
{
	t_file	file;
	t_u32a	res;

	file = ft_read_file(fname);
	if (!file.content)
		return (0);
	res = ft_parse_scene(scene, file);
	ft_close_file(&file);
	return (res);
}
