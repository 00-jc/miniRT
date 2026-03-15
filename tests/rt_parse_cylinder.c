/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parse_cylinder.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 12:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/03/15 18:21:14 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_parser/rt_parser.h"
#include "hint.h"
#include "io.h"

#define EPSILON 1e-6
#define CY_HAPPY       "0.0,0.0,-10.0 0.0,1.0,0.0 5.0 20.0 255,255,255"
#define CY_BAD_COORDS  "0.0,0.00.0 0.0,1.0,0.0 5.0 20.0 255,255,255"
#define CY_AXIS_OVER   "0.0,0.0,0.0 0.0,1.1,0.0 5.0 20.0 255,255,255"
#define CY_BAD_WIDTH   "0.0,0.0,0.0 0.0,1.0,0.0 5.a 20.0 255,255,255"
#define CY_BAD_COLOR   "0.0,0.0,0.0 0.0,1.0,0.0 5.0 20.0 256,255,255"
#define CY_MISS_COLOR  "0.0,0.0,0.0 0.0,1.0,0.0 5.0 20.0"
#define CY_VAL         "10.0,20.0,30.0 0.0,1.0,0.0 4.2 8.4 10,20,30"

#define MSG_HDR       "=== TEST PARSING CYLINDERS (5 errors expected)\n"
#define MSG_HAPPY     "Failed happypath for cylinder\n"
#define MSG_COORDS    "Failed errorpath bad coords\n"
#define MSG_AXIS      "Failed errorpath axis > 1.0\n"
#define MSG_WIDTH     "Failed errorpath bad width\n"
#define MSG_COLOR     "Failed errorpath bad color\n"
#define MSG_MISS      "Failed errorpath missing color\n"
#define MSG_VAL       "Failed happypath for cylinder (value)\n"

void	test_cylinder_parse_happy(void);
void	test_cylinder_parse_errors(void);
void	test_cylinder_parse_value(void);

void	test_cylinder_parse_happy(void)
{
	t_tokenizer	t;
	t_vec		cyls;

	ft_printf(MSG_HDR);
	cyls = ft_vec_new(4, sizeof(t_RTCylinder));
	t = ft_tokenizer_over((char *)CY_HAPPY,
			sizeof(CY_HAPPY) - 1);
	ft_pin_invariant_msg(
		rt_parse_cylinder(&t, &cyls) == OK,
		(char *)MSG_HAPPY);
	ft_vec_free(&cyls);
}

void	test_cylinder_parse_errors(void)
{
	t_tokenizer	t;
	t_vec		cyls;

	cyls = ft_vec_new(4, sizeof(t_RTCylinder));
	t = ft_tokenizer_over((char *)CY_BAD_COORDS,
			sizeof(CY_BAD_COORDS) - 1);
	ft_pin_invariant_msg(rt_parse_cylinder(&t, &cyls) == KO,
		(char *)MSG_COORDS);
	t = ft_tokenizer_over((char *)CY_AXIS_OVER,
			sizeof(CY_AXIS_OVER) - 1);
	ft_pin_invariant_msg(rt_parse_cylinder(&t, &cyls) == KO,
		(char *)MSG_AXIS);
	t = ft_tokenizer_over((char *)CY_BAD_WIDTH,
			sizeof(CY_BAD_WIDTH) - 1);
	ft_pin_invariant_msg(rt_parse_cylinder(&t, &cyls) == KO,
		(char *)MSG_WIDTH);
	t = ft_tokenizer_over((char *)CY_BAD_COLOR,
			sizeof(CY_BAD_COLOR) - 1);
	ft_pin_invariant_msg(rt_parse_cylinder(&t, &cyls) == KO,
		(char *)MSG_COLOR);
	t = ft_tokenizer_over((char *)CY_MISS_COLOR,
			sizeof(CY_MISS_COLOR) - 1);
	ft_pin_invariant_msg(rt_parse_cylinder(&t, &cyls) == KO,
		(char *)MSG_MISS);
	ft_vec_free(&cyls);
}

void	test_cylinder_parse_value(void)
{
	t_tokenizer		t;
	t_vec			cyls;
	t_RTCylinder	*cy;
	t_3dcoords		norm;

	cyls = ft_vec_new(4, sizeof(t_RTCylinder));
	t = ft_tokenizer_over((char *)CY_VAL,
			sizeof(CY_VAL) - 1);
	ft_pin_invariant_msg(rt_parse_cylinder(&t, &cyls) == OK,
		(char *)MSG_VAL);
	cy = (t_RTCylinder *)ft_vec_get(&cyls, 0,
			sizeof(t_RTCylinder));
	norm = ft_3dunit((t_3dcoords){0.0, 1.0, 0.0, 0.0});
	ft_pin_invariant_msg(cy != NULL, (char *)"VEC NULL");
	ft_pin_invariant_msg(cy->coords.x == 10.0
		&& cy->coords.y == 20.0
		&& cy->coords.z == 30.0
		&& ft_fabs(cy->axis.y - norm.y) < EPSILON
		&& ft_fabs(cy->wh.x - 4.2) < EPSILON
		&& ft_fabs(cy->wh.y - 8.4) < EPSILON
		&& (cy->color & 0xFF0000) == 0x0A0000
		&& (cy->color & 0x00FF00) == 0x001400
		&& (cy->color & 0x0000FF) == 0x00001E,
		(char *)MSG_VAL);
	ft_vec_free(&cyls);
}

int	main(void)
{
	test_cylinder_parse_happy();
	test_cylinder_parse_errors();
	test_cylinder_parse_value();
}
