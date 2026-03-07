/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parse_camera.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 12:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/03/07 18:30:52 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_parser/rt_parser.h"
#include "hint.h"
#include "io.h"

#define CM_HAPPY       "0.0,0.0,-10.0 0.0,1.0,0.0 90"
#define CM_FOV_ZERO    "0.0,0.0,0.0 0.0,0.0,1.0 0"
#define CM_FOV_180     "0.0,0.0,0.0 1.0,0.0,0.0 180"
#define CM_BAD_COORDS  "0.0,0.00.0 0.0,1.0,0.0 90"
#define CM_BAD_VEC     "0.0,0.0,0.0 0.0,1.00.0 90"
#define CM_FOV_OVER    "0.0,0.0,0.0 0.0,1.0,0.0 181"
#define CM_MISS_FOV    "0.0,0.0,0.0 0.0,1.0,0.0"
#define CM_VAL         "10.0,20.0,30.0 0.0,1.0,0.0 70"

#define MSG_HDR       "=== TEST PARSING CAMERA (5 errors expected)\n"
#define MSG_HAPPY     "Failed happypath for camera\n"
#define MSG_FZERO     "Failed happypath camera (fov 0)\n"
#define MSG_F180      "Failed happypath camera (fov 180)\n"
#define MSG_COORDS    "Failed errorpath bad coords\n"
#define MSG_VEC       "Failed errorpath bad vector\n"
#define MSG_FOVER     "Failed errorpath fov > 180\n"
#define MSG_MISS      "Failed errorpath missing fov\n"
#define MSG_DUP       "Failed errorpath duplicate camera\n"
#define MSG_VAL       "Failed happypath camera (value)\n"

void	test_camera_parse_happy(void);
void	test_camera_parse_errors(void);
void	test_camera_parse_value(void);

void	test_camera_parse_happy(void)
{
	t_tokenizer	t;
	t_RTCamera	cam;

	ft_printf(MSG_HDR);
	cam = (t_RTCamera){0};
	t = ft_tokenizer_over((char *)CM_HAPPY,
			sizeof(CM_HAPPY) - 1);
	ft_pin_invariant_msg(
		rt_parse_camera(&t, &cam) == OK,
		(char *)MSG_HAPPY);
	cam = (t_RTCamera){0};
	t = ft_tokenizer_over((char *)CM_FOV_ZERO,
			sizeof(CM_FOV_ZERO) - 1);
	ft_pin_invariant_msg(
		rt_parse_camera(&t, &cam) == OK,
		(char *)MSG_FZERO);
	cam = (t_RTCamera){0};
	t = ft_tokenizer_over((char *)CM_FOV_180,
			sizeof(CM_FOV_180) - 1);
	ft_pin_invariant_msg(
		rt_parse_camera(&t, &cam) == OK,
		(char *)MSG_F180);
	cam = (t_RTCamera){.is_init = 1};
	ft_pin_invariant_msg(
		rt_parse_camera(&t, &cam) == KO, (char *)MSG_DUP);
}

void	test_camera_parse_errors(void)
{
	t_tokenizer	t;
	t_RTCamera	cam;

	cam = (t_RTCamera){0};
	t = ft_tokenizer_over((char *)CM_BAD_COORDS,
			sizeof(CM_BAD_COORDS) - 1);
	ft_pin_invariant_msg(
		rt_parse_camera(&t, &cam) == KO,
		(char *)MSG_COORDS);
	cam = (t_RTCamera){0};
	t = ft_tokenizer_over((char *)CM_BAD_VEC,
			sizeof(CM_BAD_VEC) - 1);
	ft_pin_invariant_msg(
		rt_parse_camera(&t, &cam) == KO,
		(char *)MSG_VEC);
	cam = (t_RTCamera){0};
	t = ft_tokenizer_over((char *)CM_FOV_OVER,
			sizeof(CM_FOV_OVER) - 1);
	ft_pin_invariant_msg(
		rt_parse_camera(&t, &cam) == KO, (char *)MSG_FOVER);
	cam = (t_RTCamera){0};
	t = ft_tokenizer_over((char *)CM_MISS_FOV,
			sizeof(CM_MISS_FOV) - 1);
	ft_pin_invariant_msg(
		rt_parse_camera(&t, &cam) == KO, (char *)MSG_MISS);
}

void	test_camera_parse_value(void)
{
	t_tokenizer	t;
	t_RTCamera	cam;

	cam = (t_RTCamera){0};
	t = ft_tokenizer_over((char *)CM_VAL,
			sizeof(CM_VAL) - 1);
	ft_pin_invariant_msg(
		rt_parse_camera(&t, &cam) == OK,
		(char *)MSG_VAL);
	ft_pin_invariant_msg(cam.coords.x == 10.0
		&& cam.coords.y == 20.0
		&& cam.coords.z == 30.0
		&& cam.axis.x == 0.0
		&& cam.axis.y == 1.0
		&& cam.axis.z == 0.0
		&& cam.fov == 70, (char *)MSG_VAL);
}

int	main(void)
{
	test_camera_parse_happy();
	test_camera_parse_errors();
	test_camera_parse_value();
}
