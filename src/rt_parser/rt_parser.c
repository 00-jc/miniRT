/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 11:53:01 by jaicastr          #+#    #+#             */
/*   Updated: 2026/03/16 03:32:18 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_parser/rt_parser.h"
#include "rt_logger/rt_errors.h"
#include "rt_logger/rt_printer.h"
#include "io.h"

__attribute__((__returns_nonnull__, __always_inline__, const))
static inline t_nonuniq_parser	rt_get_nonuniq_label(size_t idx)
{
	static t_nonuniq_parser	fns[] = {
	[RT_SPHERE_IDX] = rt_parse_sphere,
	[RT_CYLINDER_IDX] = rt_parse_cylinder,
	[RT_LIGHT_IDX] = rt_parse_light,
	[RT_PLANE_IDX] = rt_parse_plane,
	};

	return (fns[idx]);
}

__attribute__((__nonnull__(1, 2), __always_inline__))
static inline t_taggedresult	rt_handle_uniq(t_RTScene *scene,
	t_tokenizer *t, t_u16a label)
{
	if (label == RT_CAMERA)
		return (rt_parse_camera(t, &scene->rt_camera));
	return (rt_parse_ambient(t, &scene->rt_ambient));
}

__attribute__((__nonnull__(1, 2, 3), __always_inline__))
static inline t_taggedresult	rt_handle_label(t_RTScene *scene,
	t_vec aos[4], t_tokenizer *t, t_token token)
{
	t_u16a	label;
	t_u16a	vecidx;

	if (token.len == 1)
		label = ft_to_be16(*token.mem | 0x0000);
	else if (token.len == 2)
		label = ft_to_be16(*(const t_u16 * restrict const)token.mem);
	else
		return (rt_error(UNREC), KO);
	if ((label == RT_CAMERA) | (label == RT_AMBIENT))
		return (rt_handle_uniq(scene, t, label));
	if ((label != RT_LIGHT) & (label != RT_SPHERE) & (label != RT_CYLINDER)
		& (label != RT_PLANE))
		return (rt_error(UNREC), KO);
	vecidx = ((label == RT_SPHERE) * RT_AOS_SPHERE)
		| ((label == RT_LIGHT) * RT_AOS_LIGHT)
		| ((label == RT_PLANE) * RT_AOS_PLANE)
		| ((label == RT_CYLINDER) * RT_AOS_CYLINDER);
	label = label % RT_PERFECT_HASH;
	if (rt_get_nonuniq_label(label)(t, aos + vecidx) == KO)
		return (KO);
	return (OK);
}

__attribute__((__nonnull__(1, 2)))
static inline t_taggedresult	ft_parse_scene(t_RTScene *scene,
	t_vec aos[4], t_file file)
{
	t_tokenizer	tokenizer;
	t_token		token;

	tokenizer = ft_tokenizer_over(file.content, file.size);
	while (tokenizer.cc != tokenizer.max)
	{
		ft_skip_whitespace(&tokenizer);
		token = ft_eat_until(&tokenizer, set_blank);
		if (rt_handle_label(scene, aos, &tokenizer, token) == KO)
			return (KO);
	}
	if (!scene->rt_camera.is_init || !scene->rt_ambient.is_init)
		return (rt_error(NDEF), KO);
	return (OK);
}

__attribute__((__nonnull__(1, 2, 3)))
t_taggedresult	rt_parse_file_into_state(t_RTScene *scene,
		char *fname, t_arena *arena)
{
	t_file	file;
	t_vec	aos[4];

	file = ft_read_file(fname);
	if (!file.content)
		return (KO);
	if (rt_init_aos(aos) == KO)
		return (KO);
	if (ft_parse_scene(scene, aos, file) == KO)
		return (rt_free_aos(aos), KO);
	ft_close_file(&file);
	if (rt_aos_to_soa(aos, scene, arena) == KO)
		return (rt_error(SOA), rt_free_aos(aos), KO);
	rt_print_soa(scene);
	rt_free_aos(aos);
	return (OK);
}
