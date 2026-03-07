/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parse_plane.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 12:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/03/07 02:22:43 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_parser/rt_parser.h"
#include "hint.h"
#include "io.h"

#define PL_HAPPY               "0.0,0.0,-10.0 0.0,1.0,0.0 0,0,255"
#define PL_AXIS_ONE            "5.0,5.0,5.0 1.0,0.0,0.0 255,255,255"
#define PL_AXIS_DIAG           "1.0,2.0,3.0 0.5,0.5,0.5 128,128,128"
#define PL_BAD_COORDS          "0.0,0.00.0 0.0,1.0,0.0 0,0,255"
#define PL_BAD_AXIS            "0.0,0.0,0.0 0.0,1.a,0.0 0,0,255"
#define PL_BAD_COLOR           "0.0,0.0,0.0 0.0,1.0,0.0 256,0,255"
#define PL_AXIS_OVERFLOW       "0.0,0.0,0.0 0.0,1.1,0.0 0,0,255"
#define PL_AXIS_NEGATIVE       "0.0,0.0,0.0 0.0,-1.0,0.0 0,0,255"
#define PL_MISSING_AXIS        "0.0,0.0,0.0 0,0,255"
#define PL_MISSING_COLOR       "0.0,0.0,0.0 0.0,1.0,0.0"
#define PL_VAL                 "10.0,20.0,30.0 1.0,0.0,0.0 10,20,30"

#define MSG_HEADER      "=== TEST PARSING PLANES (7 errors expected)\n"
#define MSG_HAPPY       "Failed happypath for plane\n"
#define MSG_HAPPY_AXIS  "Failed happypath for plane (axis unit)\n"
#define MSG_HAPPY_DIAG  "Failed happypath for plane (diagonal axis)\n"
#define MSG_BAD_COORDS  "Failed errorpath due to bad coords\n"
#define MSG_BAD_AXIS    "Failed errorpath due to bad axis\n"
#define MSG_BAD_COLOR   "Failed errorpath due to bad color\n"
#define MSG_AXIS_OVER   "Failed errorpath due to axis > 1.0\n"
#define MSG_AXIS_NEG    "Failed errorpath due to negative axis\n"
#define MSG_MISS_AXIS   "Failed errorpath due to missing axis\n"
#define MSG_MISS_COLOR  "Failed errorpath due to missing color\n"
#define MSG_HAPPY_VAL   "Failed happypath for plane (value)\n"

void	test_plane_parse_happy(void);
void	test_plane_parse_error_fmt(void);
void	test_plane_parse_error_norm(void);
void	test_plane_parse_value(void);

void	test_plane_parse_happy(void)
{
	t_tokenizer	t;
	t_vec		planes;

	ft_printf(MSG_HEADER);
	planes = ft_vec_new(4, sizeof(t_RTPlane));
	t = ft_tokenizer_over((char *)PL_HAPPY, sizeof(PL_HAPPY) - 1);
	ft_pin_invariant_msg(rt_parse_plane(&t, &planes) == OK,
		(char *)MSG_HAPPY);
	t = ft_tokenizer_over((char *)PL_AXIS_ONE, sizeof(PL_AXIS_ONE) - 1);
	ft_pin_invariant_msg(rt_parse_plane(&t, &planes) == OK,
		(char *)MSG_HAPPY_AXIS);
	t = ft_tokenizer_over((char *)PL_AXIS_DIAG, sizeof(PL_AXIS_DIAG) - 1);
	ft_pin_invariant_msg(rt_parse_plane(&t, &planes) == OK,
		(char *)MSG_HAPPY_DIAG);
	ft_vec_free(&planes);
}

void	test_plane_parse_error_fmt(void)
{
	t_tokenizer	t;
	t_vec		planes;

	planes = ft_vec_new(4, sizeof(t_RTPlane));
	t = ft_tokenizer_over((char *)PL_BAD_COORDS, sizeof(PL_BAD_COORDS) - 1);
	ft_pin_invariant_msg(rt_parse_plane(&t, &planes) == KO,
		(char *)MSG_BAD_COORDS);
	t = ft_tokenizer_over((char *)PL_BAD_AXIS, sizeof(PL_BAD_AXIS) - 1);
	ft_pin_invariant_msg(rt_parse_plane(&t, &planes) == KO,
		(char *)MSG_BAD_AXIS);
	t = ft_tokenizer_over((char *)PL_BAD_COLOR, sizeof(PL_BAD_COLOR) - 1);
	ft_pin_invariant_msg(rt_parse_plane(&t, &planes) == KO,
		(char *)MSG_BAD_COLOR);
	t = ft_tokenizer_over((char *)PL_MISSING_AXIS,
			sizeof(PL_MISSING_AXIS) - 1);
	ft_pin_invariant_msg(rt_parse_plane(&t, &planes) == KO,
		(char *)MSG_MISS_AXIS);
	t = ft_tokenizer_over((char *)PL_MISSING_COLOR,
			sizeof(PL_MISSING_COLOR) - 1);
	ft_pin_invariant_msg(rt_parse_plane(&t, &planes) == KO,
		(char *)MSG_MISS_COLOR);
	ft_vec_free(&planes);
}

void	test_plane_parse_error_norm(void)
{
	t_tokenizer	t;
	t_vec		planes;

	planes = ft_vec_new(4, sizeof(t_RTPlane));
	t = ft_tokenizer_over((char *)PL_AXIS_OVERFLOW,
			sizeof(PL_AXIS_OVERFLOW) - 1);
	ft_pin_invariant_msg(rt_parse_plane(&t, &planes) == KO,
		(char *)MSG_AXIS_OVER);
	t = ft_tokenizer_over((char *)PL_AXIS_NEGATIVE,
			sizeof(PL_AXIS_NEGATIVE) - 1);
	ft_pin_invariant_msg(rt_parse_plane(&t, &planes) == KO,
		(char *)MSG_AXIS_NEG);
	ft_vec_free(&planes);
}

void	test_plane_parse_value(void)
{
	t_tokenizer		t;
	t_vec			planes;
	t_RTPlane		*pl;

	planes = ft_vec_new(4, sizeof(t_RTPlane));
	t = ft_tokenizer_over((char *)PL_VAL, sizeof(PL_VAL) - 1);
	ft_pin_invariant_msg(rt_parse_plane(&t, &planes) == OK,
		(char *)MSG_HAPPY_VAL);
	pl = (t_RTPlane *)ft_vec_get(&planes, 0, sizeof(t_RTPlane));
	ft_pin_invariant_msg(pl != NULL, (char *)"VEC RETURNED NULL");
	ft_pin_invariant_msg(pl->coords.x == 10.0
		&& pl->coords.y == 20.0
		&& pl->coords.z == 30.0
		&& pl->axis.x == 1.0
		&& pl->axis.y == 0.0
		&& pl->axis.z == 0.0
		&& (pl->color & 0xFF0000) == 0x0A0000
		&& (pl->color & 0x00FF00) == 0x001400
		&& (pl->color & 0x0000FF) == 0x00001E, (char *)MSG_HAPPY_VAL);
	ft_vec_free(&planes);
}

int	main(void)
{
	test_plane_parse_happy();
	test_plane_parse_error_fmt();
	test_plane_parse_error_norm();
	test_plane_parse_value();
}
