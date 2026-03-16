/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 00:33:19 by jaicastr          #+#    #+#             */
/*   Updated: 2026/03/16 03:31:52 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_PARSER_H
# define RT_PARSER_H

# include "rt_miniRT.h"
# include "tokenizer.h"
# include "vec.h"
# include "alloc.h"

# define RT_AMBIENT			0x4100ULL
# define RT_CAMERA			0x4300ULL
# define RT_LIGHT			0x4C00ULL
# define RT_SPHERE			0x7370ULL
# define RT_PLANE			0x706CULL
# define RT_CYLINDER		0x6379ULL
# define RT_PERFECT_HASH	23ULL
# define RT_AMBIENT_IDX 	11
# define RT_CAMERA_IDX		17
# define RT_LIGHT_IDX		21
# define RT_SPHERE_IDX		20
# define RT_PLANE_IDX		7
# define RT_CYLINDER_IDX	4
# define RT_AOS_SPHERE		0
# define RT_AOS_LIGHT		1
# define RT_AOS_PLANE		2
# define RT_AOS_CYLINDER	3
# define V4_CMP_OK			0xFFFFFFFFFFFFFFFFULL

typedef t_taggedresult	(*t_nonuniq_parser)(t_tokenizer *t, t_vec *)\
							__attribute__((__nonnull__(1, 2)));

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

t_taggedresult	rt_parse_file_into_state(t_RTScene *state, char *fname,\
					t_arena *arena)\
					__attribute__((__nonnull__(1, 2, 3)));

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

t_taggedresult	rt_parse_cylinder(t_tokenizer *t, t_vec *cy_vec)\
					__attribute__((__nonnull__(1, 2)));

t_taggedresult	rt_parse_camera(t_tokenizer *t, t_RTCamera *cam)\
					__attribute__((__nonnull__(1, 2)));

t_taggedresult	rt_parse_ambient(t_tokenizer *t, t_RTAmbientLight *cam)\
					__attribute__((__nonnull__(1, 2)));

t_taggedresult	rt_init_aos(t_vec aos[4]);

void			rt_free_aos(t_vec aos[4]);

t_taggedresult	rt_aos_to_soa(t_vec aos[4], t_RTScene *scene,\
					t_arena *arena)\
					__attribute__((__nonnull__(1, 2, 3)));

t_taggedresult	rt_aos_to_soa_cylinder(t_RTCylinderBuffer *buf,\
					t_vec *aos, t_arena *arena)\
					__attribute__((__nonnull__(1, 2, 3)));

t_taggedresult	rt_aos_to_soa_sphere(t_RTSphereBuffer *buf,\
					t_vec *aos, t_arena *arena)\
					__attribute__((__nonnull__(1, 2, 3)));

t_taggedresult	rt_aos_to_soa_plane(t_RTPlaneBuffer *buf,\
					t_vec *aos, t_arena *arena)\
					__attribute__((__nonnull__(1, 2, 3)));

t_taggedresult	rt_aos_to_soa_light(t_RTLightBuffer *buf,\
					t_vec *aos, t_arena *arena)\
					__attribute__((__nonnull__(1, 2, 3)));

t_taggedresult	rt_parse_display_size(int argc, t_RTContext *context,\
					const char **argv)\
					__attribute__((__nonnull__(2, 3)));
#endif
