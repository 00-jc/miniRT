/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parse_ambient.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 12:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/03/07 04:33:38 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_parser/rt_parser.h"
#include "hint.h"
#include "io.h"

#define AM_HAPPY               "0.6 255,255,255"
#define AM_BRIGHT_ZERO         "0.0 0,0,0"
#define AM_BRIGHT_ONE          "1.0 128,128,128"
#define AM_BAD_BRIGHT          "0.a 255,255,255"
#define AM_BAD_COLOR           "0.6 256,255,255"
#define AM_BRIGHT_OVER         "1.1 255,255,255"
#define AM_BRIGHT_NEG          "-0.5 255,255,255"
#define AM_MISSING_COLOR       "0.6"
#define AM_VAL                 "0.5 10,20,30"

#define MSG_HEADER      "=== TEST PARSING AMBIENT (6 errors expected)\n"
#define MSG_HAPPY       "Failed happypath for ambient\n"
#define MSG_HAPPY_ZERO  "Failed happypath for ambient (brightness 0)\n"
#define MSG_HAPPY_ONE   "Failed happypath for ambient (brightness 1)\n"
#define MSG_BAD_BRIGHT  "Failed errorpath due to bad brightness\n"
#define MSG_BAD_COLOR   "Failed errorpath due to bad color\n"
#define MSG_BRIGHT_OVER "Failed errorpath due to brightness > 1.0\n"
#define MSG_BRIGHT_NEG  "Failed errorpath due to negative brightness\n"
#define MSG_MISS_COLOR  "Failed errorpath due to missing color\n"
#define MSG_REDEF       "Failed errorpath due to redefinition\n"
#define MSG_HAPPY_VAL   "Failed happypath for ambient (value)\n"

void	test_ambient_parse_happy(void);
void	test_ambient_parse_error_fmt(void);
void	test_ambient_parse_error_range(void);
void	test_ambient_parse_value(void);

void	test_ambient_parse_happy(void)
{
	t_tokenizer			t;
	t_RTAmbientLight	ambient;

	ft_printf(MSG_HEADER);
	t = ft_tokenizer_over((char *)AM_HAPPY, sizeof(AM_HAPPY) - 1);
	ft_pin_invariant_msg(rt_parse_ambient(&t, &ambient, 0) == OK,
		(char *)MSG_HAPPY);
	t = ft_tokenizer_over((char *)AM_BRIGHT_ZERO,
			sizeof(AM_BRIGHT_ZERO) - 1);
	ft_pin_invariant_msg(rt_parse_ambient(&t, &ambient, 0) == OK,
		(char *)MSG_HAPPY_ZERO);
	t = ft_tokenizer_over((char *)AM_BRIGHT_ONE,
			sizeof(AM_BRIGHT_ONE) - 1);
	ft_pin_invariant_msg(rt_parse_ambient(&t, &ambient, 0) == OK,
		(char *)MSG_HAPPY_ONE);
}

void	test_ambient_parse_error_fmt(void)
{
	t_tokenizer			t;
	t_RTAmbientLight	ambient;

	t = ft_tokenizer_over((char *)AM_BAD_BRIGHT,
			sizeof(AM_BAD_BRIGHT) - 1);
	ft_pin_invariant_msg(rt_parse_ambient(&t, &ambient, 0) == KO,
		(char *)MSG_BAD_BRIGHT);
	t = ft_tokenizer_over((char *)AM_BAD_COLOR,
			sizeof(AM_BAD_COLOR) - 1);
	ft_pin_invariant_msg(rt_parse_ambient(&t, &ambient, 0) == KO,
		(char *)MSG_BAD_COLOR);
	t = ft_tokenizer_over((char *)AM_MISSING_COLOR,
			sizeof(AM_MISSING_COLOR) - 1);
	ft_pin_invariant_msg(rt_parse_ambient(&t, &ambient, 0) == KO,
		(char *)MSG_MISS_COLOR);
	t = ft_tokenizer_over((char *)AM_HAPPY, sizeof(AM_HAPPY) - 1);
	ft_pin_invariant_msg(rt_parse_ambient(&t, &ambient, 1) == KO,
		(char *)MSG_REDEF);
}

void	test_ambient_parse_error_range(void)
{
	t_tokenizer			t;
	t_RTAmbientLight	ambient;

	t = ft_tokenizer_over((char *)AM_BRIGHT_OVER,
			sizeof(AM_BRIGHT_OVER) - 1);
	ft_pin_invariant_msg(rt_parse_ambient(&t, &ambient, 0) == KO,
		(char *)MSG_BRIGHT_OVER);
	t = ft_tokenizer_over((char *)AM_BRIGHT_NEG,
			sizeof(AM_BRIGHT_NEG) - 1);
	ft_pin_invariant_msg(rt_parse_ambient(&t, &ambient, 0) == KO,
		(char *)MSG_BRIGHT_NEG);
}

void	test_ambient_parse_value(void)
{
	t_tokenizer			t;
	t_RTAmbientLight	ambient;

	t = ft_tokenizer_over((char *)AM_VAL, sizeof(AM_VAL) - 1);
	ft_pin_invariant_msg(rt_parse_ambient(&t, &ambient, 0) == OK,
		(char *)MSG_HAPPY_VAL);
	ft_pin_invariant_msg(ambient.brightness == 0.5
		&& (ambient.color & 0xFF0000) == 0x0A0000
		&& (ambient.color & 0x00FF00) == 0x001400
		&& (ambient.color & 0x0000FF) == 0x00001E, (char *)MSG_HAPPY_VAL);
}

int	main(void)
{
	test_ambient_parse_happy();
	test_ambient_parse_error_fmt();
	test_ambient_parse_error_range();
	test_ambient_parse_value();
}
