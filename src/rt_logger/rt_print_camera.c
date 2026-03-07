__attributes__((__always_inline__))
inline void	rt_print_camera(t_RTCamera camera)
{
	ft_printf("Object: Camera\n");
	ft_printf("\tcoords: %f, %f, %f\n", camera.coords.coord.x,
		camera.coords.coord.y, camera.coords.coord.z);
	ft_printf("\taxis: %f, %f, %f\n", camera.axis.coord.x,
		camera.axis.coord.y, camera.axis.coord.z);
	ft_printf("\tfov: %d\n", camera.fov);
	ft_printf("\tinitialization: %d\n", camera.is_init);
}
