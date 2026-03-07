#include <stdio.h>
#include <stdint.h>

#define RT_AMBIENT  0x41
#define RT_CAMERA   0x43
#define RT_LIGHT    0x4C
#define RT_SPHERE   0x7073
#define RT_PLANE    0x6C70
#define RT_CYLINDER 0x7963
# define RT_AMBIENT_IDX		2
# define RT_CAMERA_IDX		4
# define RT_LIGHT_IDX		13
# define RT_SPHERE_IDX		17
# define RT_PLANE_IDX		19
# define RT_CYLINDER_IDX	16

int main(void)
{
	uint16_t vals[] = {RT_AMBIENT, RT_CAMERA, RT_LIGHT, RT_SPHERE, RT_PLANE, RT_CYLINDER};
	const char *names[] = {"AMBIENT", "CAMERA", "LIGHT", "SPHERE", "PLANE", "CYLINDER"};
	int n = sizeof(vals) / sizeof(vals[0]);

	for (size_t i = 1; ; i++)
	{
		int collision = 0;
		for (int a = 0; a < n && !collision; a++)
			for (int b = a + 1; b < n && !collision; b++)
				if (vals[a] % i == vals[b] % i)
					collision = 1;
		if (!collision)
		{
			printf("#define RT_MOD %zu\n\n", i);
			for (int k = 0; k < n; k++)
				printf("#define RT_%s_IDX %zu\n", names[k], (size_t)(vals[k] % i));
			break;
		}
	}
	return 0;
}
