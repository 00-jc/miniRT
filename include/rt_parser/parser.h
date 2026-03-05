/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 00:33:19 by jaicastr          #+#    #+#             */
/*   Updated: 2026/03/05 23:02:27 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "miniRT.h"
# include "tokenizer.h"

typedef enum e_taggedresult
{
	OK,
	KO,
}	t_taggedresult;

typedef struct s_color_result
{
	t_taggedresult	res;
	t_u32a			color;
}	t_color_result;

typedef struct s_coord_result
{
	t_taggedresult	res;
	t_3dcoords		color;
}	t_coord_result;

t_u32a			rt_parse_file_into_state(t_RTScene *state, char *fname)\
					__attribute__((__nonnull__(1, 2)));

t_color_result	rt_parse_color(t_tokenizer *tokenizer)\
					__attribute__((__nonnull__(1)));

t_coord_result	rt_parse_coords(t_tokenizer *tokenizer)\
					__attribute__((__nonnull__(1)));

#endif
