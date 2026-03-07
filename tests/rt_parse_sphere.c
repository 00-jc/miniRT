/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parse_sphere.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 12:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/03/07 01:42:05 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_parser/rt_parser.h"
#include "hint.h"
#include "io.h"

#define SP_HAPPY               "20.0,20.0,20.0 12.6 255,128,0"
#define SP_ZEROS               "0.0,0.0,0.0 0.0 0,0,0"
#define SP_INT_COORDS          "20,20,20 5.0 128,128,128"
#define SP_BAD_COORDS          "20.0,20.020.0 12.6 255,128,0"
#define SP_BAD_DIAMETER        "20.0,20.0,20.0 12.a 255,128,0"
#define SP_BAD_COLOR           "20.0,20.0,20.0 12.6 256,128,0"
#define SP_MISSING_DIAMETER    "20.0,20.0,20.0 255,128,0"
#define SP_MISSING_COLOR       "20.0,20.0,20.0 12.6"
#define SP_NEGATIVE_DIAM       "20.0,20.0,20.0 -5.0 255,128,0"
#define SP_VAL                 "10.0,20.0,30.0 5.5 10,20,30"

#define MSG_HEADER      "=== TEST PARSING SPHERES (6 errors expected)\n"
#define MSG_HAPPY       "Failed happypath for sphere\n"
#define MSG_HAPPY_ZERO  "Failed happypath for sphere (all zeros)\n"
#define MSG_HAPPY_INT   "Failed happypath for sphere (int coords)\n"
#define MSG_BAD_COORDS  "Failed errorpath due to bad coords\n"
#define MSG_BAD_DIAM    "Failed errorpath due to bad diameter\n"
#define MSG_BAD_COLOR   "Failed errorpath due to bad color\n"
#define MSG_MISS_DIAM   "Failed errorpath due to missing diameter\n"
#define MSG_MISS_COLOR  "Failed errorpath due to missing color\n"
#define MSG_NEG_DIAM    "Failed errorpath due to negative diameter\n"
#define MSG_HAPPY_VAL   "Failed happypath for sphere (value)\n"

void	test_sphere_parse_happy(void);
void	test_sphere_parse_error(void);
void	test_sphere_parse_value(void);

void	test_sphere_parse_happy(void)
{
	t_tokenizer	t;
	t_vec		spheres;

	ft_printf(MSG_HEADER);
	spheres = ft_vec_new(4, sizeof(t_RTSphere));
	t = ft_tokenizer_over((char *)SP_HAPPY, sizeof(SP_HAPPY) - 1);
	ft_pin_invariant_msg(rt_parse_sphere(&t, &spheres) == OK,
		(char *)MSG_HAPPY);
	t = ft_tokenizer_over((char *)SP_ZEROS, sizeof(SP_ZEROS) - 1);
	ft_pin_invariant_msg(rt_parse_sphere(&t, &spheres) == OK,
		(char *)MSG_HAPPY_ZERO);
	t = ft_tokenizer_over((char *)SP_INT_COORDS, sizeof(SP_INT_COORDS) - 1);
	ft_pin_invariant_msg(rt_parse_sphere(&t, &spheres) == OK,
		(char *)MSG_HAPPY_INT);
	ft_vec_free(&spheres);
}

void	test_sphere_parse_error(void)
{
	t_tokenizer	t;
	t_vec		spheres;

	spheres = ft_vec_new(4, sizeof(t_RTSphere));
	t = ft_tokenizer_over((char *)SP_BAD_COORDS, sizeof(SP_BAD_COORDS) - 1);
	ft_pin_invariant_msg(rt_parse_sphere(&t, &spheres) == KO,
		(char *)MSG_BAD_COORDS);
	t = ft_tokenizer_over((char *)SP_BAD_DIAMETER,
			sizeof(SP_BAD_DIAMETER) - 1);
	ft_pin_invariant_msg(rt_parse_sphere(&t, &spheres) == KO,
		(char *)MSG_BAD_DIAM);
	t = ft_tokenizer_over((char *)SP_BAD_COLOR, sizeof(SP_BAD_COLOR) - 1);
	ft_pin_invariant_msg(rt_parse_sphere(&t, &spheres) == KO,
		(char *)MSG_BAD_COLOR);
	t = ft_tokenizer_over((char *)SP_MISSING_DIAMETER,
			sizeof(SP_MISSING_DIAMETER) - 1);
	ft_pin_invariant_msg(rt_parse_sphere(&t, &spheres) == KO,
		(char *)MSG_MISS_DIAM);
	t = ft_tokenizer_over((char *)SP_MISSING_COLOR,
			sizeof(SP_MISSING_COLOR) - 1);
	ft_pin_invariant_msg(rt_parse_sphere(&t, &spheres) == KO,
		(char *)MSG_MISS_COLOR);
	ft_vec_free(&spheres);
}

void	test_sphere_parse_value(void)
{
	t_tokenizer		t;
	t_vec			spheres;
	t_RTSphere		*sp;

	spheres = ft_vec_new(4, sizeof(t_RTSphere));
	t = ft_tokenizer_over((char *)SP_NEGATIVE_DIAM,
			sizeof(SP_NEGATIVE_DIAM) - 1);
	ft_pin_invariant_msg(rt_parse_sphere(&t, &spheres) == KO,
		(char *)MSG_NEG_DIAM);
	t = ft_tokenizer_over((char *)SP_VAL, sizeof(SP_VAL) - 1);
	ft_pin_invariant_msg(rt_parse_sphere(&t, &spheres) == OK,
		(char *)MSG_HAPPY_VAL);
	sp = (t_RTSphere *)ft_vec_get(&spheres, 0, sizeof(t_RTSphere));
	ft_pin_invariant_msg(sp != NULL, (char *)"VEC RETURNED NULL");
	ft_pin_invariant_msg(sp->coords.x == 10.0
		&& sp->coords.y == 20.0
		&& sp->coords.z == 30.0
		&& sp->diameter == 5.5
		&& (sp->color & 0xFF0000) == 0x0A0000
		&& (sp->color & 0x00FF00) == 0x001400
		&& (sp->color & 0x0000FF) == 0x00001E, (char *)MSG_HAPPY_VAL);
	ft_vec_free(&spheres);
}

int	main(void)
{
	test_sphere_parse_happy();
	test_sphere_parse_error();
	test_sphere_parse_value();
}
