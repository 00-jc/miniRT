/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_cast_nonuniq.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoria <asoria@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 18:59:33 by asoria            #+#    #+#             */
/*   Updated: 2026/03/12 19:02:03 by asoria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static inline void	rt_cast_spheres(t_RTRay ray, t_RTScene *scene,
		t_RTHit *hit, double *closest)
{
    double  t;
    size_t  i;

    i = 0;
    while (i < scene->rt_sphere_buffer.size)
    {
        t = rt_intersect_sphere(ray, i, &scene->rt_sphere_buffer);
        if (t > 0 && t < *closest)
        {
            *closest = t;
            hit->t = t;
            hit->color = scene->rt_sphere_buffer.color[i];
            hit->point = ft_3dadd(ray.origin,
                ft_3dmul(ray.dir, (t_3dcoords){t, t, t, 0}));
            hit->normal = rt_sphere_normal(hit->point, i, &scene->rt_sphere_buffer);
        }
        i++;
    }
}

static inline void	rt_cast_planes(t_RTRay ray, t_RTScene *scene,
		t_RTHit *hit, double *closest)
{
    double  t;
    size_t  i;

    i = 0;
    while (i < scene->rt_plane_buffer.size)
    {
        t = rt_intersect_plane(ray, i, &scene->rt_plane_buffer);
        if (t > 0 && t < *closest)
        {
            *closest = t;
            hit->t = t;
            hit->color = scene->rt_plane_buffer.color[i];
            hit->point = ft_3dadd(ray.origin,
                ft_3dmul(ray.dir, (t_3dcoords){t, t, t, 0}));
            hit->normal = scene->rt_plane_buffer.axis[i];
        }
        i++;
    }
}

static inline void	rt_cast_cylinders(t_RTRay ray, t_RTScene *scene,
		t_RTHit *hit, double *closest)
{
    double  t;
    size_t  i;

    i = 0;
    while (i < scene->rt_cylinder_buffer.size)
    {
        t = rt_intersect_cylinder(ray, i, &scene->rt_cylinder_buffer);
        if (t > 0 && t < *closest)
        {
            *closest = t;
            hit->t = t;
            hit->color = scene->rt_cylinder_buffer.color[i];
            hit->point = ft_3dadd(ray.origin,
                ft_3dmul(ray.dir, (t_3dcoords){t, t, t, 0}));
            hit->normal = rt_cylinder_normal(hit->point, i, &scene->rt_cylinder_buffer);
        }
        i++;
    }
}
