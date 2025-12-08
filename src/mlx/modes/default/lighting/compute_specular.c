/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   compute_specular.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: alkuijte <alkuijte@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/12/08 13:19:38 by alkuijte      #+#    #+#                 */
/*   Updated: 2025/12/08 14:47:30 by alkuijte      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_declarations.h>
#include <minirt_math.h>
#include <minirt_mlx.h>
#include <math.h>

// function computeSpecular(hit, light, viewDir):
//     N = normalize(hit.normal)                # Surface normal
//     L = normalize(light.position - hit.point)  # Direction to light
//     V = normalize(viewDir)                   # Direction to viewer/camera

//     dotLN = dot(L, N)
//     if dotLN <= 0:
//         return 0                            # Light is behind the surface → no specular

//     # Reflection vector of light around the normal
//     R = normalize(2 * dotLN * N - L)
//     dotRV = dot(R, V)

//     if dotRV > 0:
//         specular = hit.material.k_s * (dotRV ^ hit.material.alpha) * light.i_s
//     else:
//         specular = 0

//     return specular


t_vec4	compute_specular(t_vec4 light_col, t_material *material, t_vec3 N, t_vec3 V, t_vec3 L, double dotLN)
{
	t_vec4 specular = {0.0f, 0.0f, 0.0f, 0.0f};
	t_vec3 R;
	double	dotRV;
	double	specF;

	if (dotLN > 0.0f)
	{
		R = vec3_normalise(vec3_sub(vec3_scalar_mul(N, 2.0f * dotLN), L));
		dotRV = fmaxf(vec3_dot_product(R, V), 0.0f);
		specF = powf(dotRV, material->shininess);
		specular =  vec3_scalar_mul(light_col, material->spec_reflectivity * specF); // potentially add liight specular reflectivity
	}
	return (specular);
}