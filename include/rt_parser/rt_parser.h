/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 00:33:19 by jaicastr          #+#    #+#             */
/*   Updated: 2026/03/07 02:47:03 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_PARSER_H
# define RT_PARSER_H

# include "rt_miniRT.h"
# include "tokenizer.h"
# include "vec.h"

typedef enum e_taggedresult
{
	KO = 0,
	OK = 1
}	t_taggedresult;

typedef struct s_color_result
{
	t_taggedresult	res;
	t_u32a			color;
}	t_color_result;

typedef struct s_coord_result
{
	t_taggedresult	res;
	t_3dcoords		coord;
}	t_coord_result;

typedef struct s_double_res
{
	t_taggedresult	res;
	double			d;
}	t_double_res;

typedef struct s_unsigned_res
{
	t_taggedresult	res;
	size_t			u;
}	t_unsigned_res;

t_u32a			rt_parse_file_into_state(t_RTScene *state, char *fname)\
					__attribute__((__nonnull__(1, 2)));

t_color_result	rt_parse_color(t_tokenizer *tokenizer)\
					__attribute__((__nonnull__(1)));

t_coord_result	rt_parse_coords(t_tokenizer *tokenizer)\
					__attribute__((__nonnull__(1)));

t_double_res	rt_parse_double(t_tokenizer *t)\
					__attribute__((__nonnull__(1)));

t_unsigned_res	rt_parse_usigned(t_tokenizer *t)\
					__attribute__((__nonnull__(1)));

t_taggedresult	rt_parse_sphere(t_tokenizer *t, t_vec *sphere_vec)\
					__attribute__((__nonnull__(1, 2)));

t_taggedresult	rt_parse_plane(t_tokenizer *t, t_vec *plane_vec)\
					__attribute__((__nonnull__(1, 2)));

t_taggedresult	rt_parse_light(t_tokenizer *t, t_vec *light_vec)\
					__attribute__((__nonnull__(1, 2)));
#endif
