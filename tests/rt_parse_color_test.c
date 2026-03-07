/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parse_color_test.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 17:28:27 by jaicastr          #+#    #+#             */
/*   Updated: 2026/03/07 18:28:39 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_parser/rt_parser.h"
#include "hint.h"
#include "io.h"

#define COL_HAPPY              "255,128,0"
#define COL_ZEROS              "0,0,0"
#define COL_MAX                "255,255,255"
#define COL_NO_COMMA1          "255128,0"
#define COL_NEWLINE            "255,128\n0"
#define COL_TRAIL_COMMA        "255,128,"
#define COL_ALPHA              "255,12a,0"
#define COL_NEGATIVE           "-1,128,0"
#define COL_OVERFLOW           "256,128,0"
#define COL_FLOAT              "255.0,128,0"
#define COL_VAL_MIXED          "10,20,30"

#define MSG_HEADER      "=== TEST PARSING COLORS (7 errors expected)\n"
#define MSG_HAPPY       "Failed happypath for colors\n"
#define MSG_HAPPY_ZERO  "Failed happypath for colors (all zeros)\n"
#define MSG_HAPPY_MAX   "Failed happypath for colors (all max)\n"
#define MSG_NO_COMMA    "Failed errorpath due to missing comma\n"
#define MSG_NO_FINAL    "Failed errorpath due to missing final digit\n"
#define MSG_ALPHA       "Failed errorpath due to mixed letters and numbers\n"
#define MSG_NEGATIVE    "Failed errorpath due to negative value\n"
#define MSG_OVERFLOW    "Failed errorpath due to value > 255\n"
#define MSG_FLOAT       "Failed errorpath due to float notation\n"
#define MSG_HAPPY_VAL   "Failed happypath for colors (value)\n"

void	test_color_parse_value(void);
void	test_color_parse_error(void);
void	test_color_parse_happy(void);

void	test_color_parse_happy(void)
{
	t_tokenizer	t;

	ft_printf(MSG_HEADER);
	t = ft_tokenizer_over((char *)COL_HAPPY, sizeof(COL_HAPPY) - 1);
	ft_pin_invariant_msg(rt_parse_color(&t).res == OK,
		(char *)MSG_HAPPY);
	t = ft_tokenizer_over((char *)COL_ZEROS, sizeof(COL_ZEROS) - 1);
	ft_pin_invariant_msg(rt_parse_color(&t).res == OK,
		(char *)MSG_HAPPY_ZERO);
	t = ft_tokenizer_over((char *)COL_MAX, sizeof(COL_MAX) - 1);
	ft_pin_invariant_msg(rt_parse_color(&t).res == OK,
		(char *)MSG_HAPPY_MAX);
}

void	test_color_parse_error(void)
{
	t_tokenizer	t;

	t = ft_tokenizer_over((char *)COL_NO_COMMA1, sizeof(COL_NO_COMMA1) - 1);
	ft_pin_invariant_msg(rt_parse_color(&t).res == KO,
		(char *)MSG_NO_COMMA);
	t = ft_tokenizer_over((char *)COL_NEWLINE, sizeof(COL_NEWLINE) - 1);
	ft_pin_invariant_msg(rt_parse_color(&t).res == KO,
		(char *)MSG_NO_COMMA);
	t = ft_tokenizer_over((char *)COL_TRAIL_COMMA, sizeof(COL_TRAIL_COMMA) - 1);
	ft_pin_invariant_msg(rt_parse_color(&t).res == KO,
		(char *)MSG_NO_FINAL);
	t = ft_tokenizer_over((char *)COL_ALPHA, sizeof(COL_ALPHA) - 1);
	ft_pin_invariant_msg(rt_parse_color(&t).res == KO,
		(char *)MSG_ALPHA);
	t = ft_tokenizer_over((char *)COL_NEGATIVE, sizeof(COL_NEGATIVE) - 1);
	ft_pin_invariant_msg(rt_parse_color(&t).res == KO,
		(char *)MSG_NEGATIVE);
	t = ft_tokenizer_over((char *)COL_OVERFLOW, sizeof(COL_OVERFLOW) - 1);
	ft_pin_invariant_msg(rt_parse_color(&t).res == KO,
		(char *)MSG_OVERFLOW);
	t = ft_tokenizer_over((char *)COL_FLOAT, sizeof(COL_FLOAT) - 1);
	ft_pin_invariant_msg(rt_parse_color(&t).res == KO,
		(char *)MSG_FLOAT);
}

void	test_color_parse_value(void)
{
	t_tokenizer		t;
	t_color_result	col;

	t = ft_tokenizer_over((char *)COL_HAPPY, sizeof(COL_HAPPY) - 1);
	col = rt_parse_color(&t);
	ft_pin_invariant_msg((col.color & 0xFF0000) == 0xFF0000
		&& (col.color & 0x00FF00) == 0x008000
		&& (col.color & 0x0000FF) == 0x000000, (char *)MSG_HAPPY_VAL);
	t = ft_tokenizer_over((char *)COL_VAL_MIXED, sizeof(COL_VAL_MIXED) - 1);
	col = rt_parse_color(&t);
	ft_pin_invariant_msg((col.color & 0xFF0000) == 0x0A0000
		&& (col.color & 0x00FF00) == 0x001400
		&& (col.color & 0x0000FF) == 0x00001E, (char *)MSG_HAPPY_VAL);
}

int	main(void)
{
	test_color_parse_happy();
	test_color_parse_error();
	test_color_parse_value();
}
