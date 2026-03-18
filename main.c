#include <stdio.h>
#include <stdint.h>

# define RT_AMBIENT			0x4100ULL
# define RT_CAMERA			0x4300ULL
# define RT_LIGHT			0x4C00ULL
# define RT_SPHERE			0x7370ULL
# define RT_PLANE			0x706CULL
# define RT_CYLINDER		0x6379ULL
# define RT_CONE			0x636fULL

int main(void)
{
	uint16_t vals[] = {RT_AMBIENT, RT_CAMERA, RT_LIGHT, RT_SPHERE, RT_PLANE, RT_CYLINDER, RT_CONE};
	const char *names[] = {"AMBIENT", "CAMERA", "LIGHT", "SPHERE", "PLANE", "CYLINDER", "CONE"};
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
