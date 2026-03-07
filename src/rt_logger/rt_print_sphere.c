__attributes__((__always_inline__))
inline void	rt_print_sphere(t_RTSphere sphere)
{
	ft_printf("Object: Sphere\n");
	ft_printf("\tcoords: %f, %f, %f\n", sphere.coords.coord.x,
		sphere.coords.coord.y, sphere.coords.coord.z);
	ft_printf("\tdiameter: %f\n", sphere.diameter);
	ft_printf("\tcolor: %x\n", sphere.color);
}
