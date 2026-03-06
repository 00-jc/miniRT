/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_coord_test.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 17:28:27 by jaicastr          #+#    #+#             */
/*   Updated: 2026/03/06 17:57:50 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "rt_parser/parser.h"
#include "hint.h"
#include "io.h"

#define COORD_HAPPY            "20.0,20.0,20.0"
#define COORD_MIXED            "20,20.0,20.0"
#define COORD_NO_COMMA1        "20,20.020.0"
#define COORD_NO_COMMA1_SZ     "20.0,20.020.0"
#define COORD_NEWLINE          "20,20.0\n20.0"
#define COORD_NEWLINE_SZ       "20.0,20.0\n20.0"
#define COORD_TRAIL_COMMA      "20,20.0,"
#define COORD_TRAIL_COMMA_SZ   "20.0,20.0,"
#define COORD_ALPHA            "20,20.a,20.0"
#define COORD_ALPHA_SZ         "20.0,20.0,"
#define COORD_VAL_MIXED        "20.0,20,20.0"

#define MSG_HEADER      "=== TEST PARSING COORDS (4 errors expected)\n"
#define MSG_HAPPY       "Failed happypath for colors\n"
#define MSG_HAPPY_MIXED "Failed happypath for colors with mixed notation\n"
#define MSG_NO_COMMA    "Failed errorpath due to missing comma\n"
#define MSG_NO_FINAL    "Failed errorpath due to missing final digit\n"
#define MSG_ALPHA		"Failed errorpath due to mixed letters and numbers\n"
#define MSG_HAPPY_VAL   "Failed happypath for colors (value)\n"

void	test_coord_parse(void);
void	test_coord_parse_value(void);

void	test_coord_parse(void)
{
	t_tokenizer	t;

	ft_printf(MSG_HEADER);
	t = ft_tokenizer_over((char *)COORD_HAPPY, sizeof(COORD_HAPPY) - 1);
	ft_pin_invariant_msg(rt_parse_coords(&t).res == OK,
		(char *)MSG_HAPPY);
	t = ft_tokenizer_over((char *)COORD_MIXED, sizeof(COORD_MIXED) - 1);
	ft_pin_invariant_msg(rt_parse_coords(&t).res == OK,
		(char *)MSG_HAPPY_MIXED);
	t = ft_tokenizer_over((char *)COORD_NO_COMMA1,
			sizeof(COORD_NO_COMMA1_SZ) - 1);
	ft_pin_invariant_msg(rt_parse_coords(&t).res == KO,
		(char *)MSG_NO_COMMA);
	t = ft_tokenizer_over((char *)COORD_NEWLINE, sizeof(COORD_NEWLINE_SZ) - 1);
	ft_pin_invariant_msg(rt_parse_coords(&t).res == KO,
		(char *)MSG_NO_COMMA);
	t = ft_tokenizer_over((char *)COORD_TRAIL_COMMA,
			sizeof(COORD_TRAIL_COMMA_SZ) - 1);
	ft_pin_invariant_msg(rt_parse_coords(&t).res == KO,
		(char *)MSG_NO_FINAL);
	t = ft_tokenizer_over((char *)COORD_ALPHA, sizeof(COORD_ALPHA_SZ) - 1);
	ft_pin_invariant_msg(rt_parse_coords(&t).res == KO,
		(char *)MSG_ALPHA);
}

void	test_coord_parse_value(void)
{
	t_tokenizer		t;
	t_coord_result	coord;

	t = ft_tokenizer_over((char *)COORD_HAPPY, sizeof(COORD_HAPPY) - 1);
	coord = rt_parse_coords(&t);
	ft_pin_invariant_msg(coord.coord.x == 20.0 && coord.coord.y == 20.0
		&& coord.coord.z == 20.0, (char *)MSG_HAPPY_VAL);
	t = ft_tokenizer_over((char *)COORD_VAL_MIXED, sizeof(COORD_HAPPY) - 1);
	coord = rt_parse_coords(&t);
	ft_pin_invariant_msg(coord.coord.x == 20.0 && coord.coord.y == 20.0
		&& coord.coord.z == 20.0, (char *)MSG_HAPPY_VAL);
}

int	main(void)
{
	test_coord_parse();
	test_coord_parse_value();
}
