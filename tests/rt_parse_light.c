/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parse_light.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 12:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/03/07 02:52:48 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_parser/rt_parser.h"
#include "hint.h"
#include "io.h"

#define LT_HAPPY               "0.0,0.0,-10.0 0.6 255,255,255"
#define LT_BRIGHT_ZERO         "0.0,0.0,0.0 0.0 0,0,0"
#define LT_BRIGHT_ONE          "5.0,5.0,5.0 1.0 128,128,128"
#define LT_BAD_COORDS          "0.0,0.00.0 0.6 255,255,255"
#define LT_BAD_BRIGHT          "0.0,0.0,0.0 0.a 255,255,255"
#define LT_BAD_COLOR           "0.0,0.0,0.0 0.6 256,255,255"
#define LT_BRIGHT_OVER         "0.0,0.0,0.0 1.1 255,255,255"
#define LT_BRIGHT_NEG          "0.0,0.0,0.0 -0.5 255,255,255"
#define LT_MISSING_BRIGHT      "0.0,0.0,0.0 255,255,255"
#define LT_MISSING_COLOR       "0.0,0.0,0.0 0.6"
#define LT_VAL                 "10.0,20.0,30.0 0.5 10,20,30"

#define MSG_HEADER      "=== TEST PARSING LIGHTS (7 errors expected)\n"
#define MSG_HAPPY       "Failed happypath for light\n"
#define MSG_HAPPY_ZERO  "Failed happypath for light (brightness 0)\n"
#define MSG_HAPPY_ONE   "Failed happypath for light (brightness 1)\n"
#define MSG_BAD_COORDS  "Failed errorpath due to bad coords\n"
#define MSG_BAD_BRIGHT  "Failed errorpath due to bad brightness\n"
#define MSG_BAD_COLOR   "Failed errorpath due to bad color\n"
#define MSG_BRIGHT_OVER "Failed errorpath due to brightness > 1.0\n"
#define MSG_BRIGHT_NEG  "Failed errorpath due to negative brightness\n"
#define MSG_MISS_BRIGHT "Failed errorpath due to missing brightness\n"
#define MSG_MISS_COLOR  "Failed errorpath due to missing color\n"
#define MSG_HAPPY_VAL   "Failed happypath for light (value)\n"

void	test_light_parse_happy(void);
void	test_light_parse_error_fmt(void);
void	test_light_parse_error_range(void);
void	test_light_parse_value(void);

void	test_light_parse_happy(void)
{
	t_tokenizer	t;
	t_vec		lights;

	ft_printf(MSG_HEADER);
	lights = ft_vec_new(4, sizeof(t_RTLight));
	t = ft_tokenizer_over((char *)LT_HAPPY, sizeof(LT_HAPPY) - 1);
	ft_pin_invariant_msg(rt_parse_light(&t, &lights) == OK,
		(char *)MSG_HAPPY);
	t = ft_tokenizer_over((char *)LT_BRIGHT_ZERO,
			sizeof(LT_BRIGHT_ZERO) - 1);
	ft_pin_invariant_msg(rt_parse_light(&t, &lights) == OK,
		(char *)MSG_HAPPY_ZERO);
	t = ft_tokenizer_over((char *)LT_BRIGHT_ONE,
			sizeof(LT_BRIGHT_ONE) - 1);
	ft_pin_invariant_msg(rt_parse_light(&t, &lights) == OK,
		(char *)MSG_HAPPY_ONE);
	ft_vec_free(&lights);
}

void	test_light_parse_error_fmt(void)
{
	t_tokenizer	t;
	t_vec		lights;

	lights = ft_vec_new(4, sizeof(t_RTLight));
	t = ft_tokenizer_over((char *)LT_BAD_COORDS,
			sizeof(LT_BAD_COORDS) - 1);
	ft_pin_invariant_msg(rt_parse_light(&t, &lights) == KO,
		(char *)MSG_BAD_COORDS);
	t = ft_tokenizer_over((char *)LT_BAD_BRIGHT,
			sizeof(LT_BAD_BRIGHT) - 1);
	ft_pin_invariant_msg(rt_parse_light(&t, &lights) == KO,
		(char *)MSG_BAD_BRIGHT);
	t = ft_tokenizer_over((char *)LT_BAD_COLOR,
			sizeof(LT_BAD_COLOR) - 1);
	ft_pin_invariant_msg(rt_parse_light(&t, &lights) == KO,
		(char *)MSG_BAD_COLOR);
	t = ft_tokenizer_over((char *)LT_MISSING_BRIGHT,
			sizeof(LT_MISSING_BRIGHT) - 1);
	ft_pin_invariant_msg(rt_parse_light(&t, &lights) == KO,
		(char *)MSG_MISS_BRIGHT);
	t = ft_tokenizer_over((char *)LT_MISSING_COLOR,
			sizeof(LT_MISSING_COLOR) - 1);
	ft_pin_invariant_msg(rt_parse_light(&t, &lights) == KO,
		(char *)MSG_MISS_COLOR);
	ft_vec_free(&lights);
}

void	test_light_parse_error_range(void)
{
	t_tokenizer	t;
	t_vec		lights;

	lights = ft_vec_new(4, sizeof(t_RTLight));
	t = ft_tokenizer_over((char *)LT_BRIGHT_OVER,
			sizeof(LT_BRIGHT_OVER) - 1);
	ft_pin_invariant_msg(rt_parse_light(&t, &lights) == KO,
		(char *)MSG_BRIGHT_OVER);
	t = ft_tokenizer_over((char *)LT_BRIGHT_NEG,
			sizeof(LT_BRIGHT_NEG) - 1);
	ft_pin_invariant_msg(rt_parse_light(&t, &lights) == KO,
		(char *)MSG_BRIGHT_NEG);
	ft_vec_free(&lights);
}

void	test_light_parse_value(void)
{
	t_tokenizer		t;
	t_vec			lights;
	t_RTLight		*lt;

	lights = ft_vec_new(4, sizeof(t_RTLight));
	t = ft_tokenizer_over((char *)LT_VAL, sizeof(LT_VAL) - 1);
	ft_pin_invariant_msg(rt_parse_light(&t, &lights) == OK,
		(char *)MSG_HAPPY_VAL);
	lt = (t_RTLight *)ft_vec_get(&lights, 0, sizeof(t_RTLight));
	ft_pin_invariant_msg(lt != NULL, (char *)"VEC RETURNED NULL");
	ft_pin_invariant_msg(lt->coords.x == 10.0
		&& lt->coords.y == 20.0
		&& lt->coords.z == 30.0
		&& lt->brightness == 0.5
		&& (lt->color & 0xFF0000) == 0x0A0000
		&& (lt->color & 0x00FF00) == 0x001400
		&& (lt->color & 0x0000FF) == 0x00001E, (char *)MSG_HAPPY_VAL);
	ft_vec_free(&lights);
}

int	main(void)
{
	test_light_parse_happy();
	test_light_parse_error_fmt();
	test_light_parse_error_range();
	test_light_parse_value();
}
