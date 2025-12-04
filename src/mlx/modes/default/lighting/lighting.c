/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lighting.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: alkuijte <alkuijte@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/12/04 13:31:52 by alkuijte      #+#    #+#                 */
/*   Updated: 2025/12/04 16:55:48 by alkuijte      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <MLX42.h>
#include <math.h>
#include <minirt_declarations.h>
#include <minirt_math.h>
#include <minirt_math_superquadrics.h>
#include <minirt_mlx.h>
#include <stdio.h>

/*
function compute_reflection(scene, hit, ray, depth):
    if hit.obj.material.reflectivity <= 0:
        return vec3(0, 0, 0)  # no reflection

    # 1. Compute reflected ray
    reflected_dir = normalize(reflect(ray.dir, hit.normal))
    reflected_origin = hit.point + hit.normal * EPSILON  # avoid self-intersection

    reflected_ray = { origin: reflected_origin, dir: reflected_dir }

    # 2. Recurse
    reflected_color = recursive_default_colour(scene, reflected_ray, depth + 1)

    # 3. Weight by reflectivity
    return reflected_color * hit.obj.material.reflectivity

function fresnel_blend(local_color, reflected_color, material, cos_theta):
    # Compute Fresnel term (Schlick approximation)
    F = fresnel_schlick(cos_theta, material.ior)

    # Weight reflection by Fresnel, local color by (1 - Fresnel)
    return local_color * (1 - F) + reflected_color * F

function compute_diffuse(hit, light):
    L = normalize(light.position - hit.point)  # light direction
    N = normalize(hit.normal)

    # Diffuse intensity = max(0, N · L)
    intensity = max(0, dot(N, L))

    return hit.obj.material.diffuse_color * light.color * intensity

function compute_specular(hit, view_dir, light):
    L = normalize(light.position - hit.point)  # light direction
    N = normalize(hit.normal)
    V = normalize(-view_dir)                   # direction to camera

    # Phong model: R = reflect(-L, N)
    R = reflect(-L, N)
    spec_intensity = pow(max(0, dot(R, V)), hit.obj.material.shininess)

    return light.color * hit.obj.material.specular_color * spec_intensity

function in_shadow(scene, point, light):
    dir_to_light = normalize(light.position - point)
    dist_to_light = length(light.position - point)
    shadow_ray = { origin: point + dir_to_light * EPSILON, dir: dir_to_light }

    hit_shadow = find_closest_intersection(scene, shadow_ray)
    if hit_shadow exists and hit_shadow.t < dist_to_light:
        return true  # blocked
    return false

function compute_lighting(scene, hit, view_dir):
    color = vec3(0, 0, 0)
    for light in scene.lights:
        if not in_shadow(scene, hit.point, light):
            color += compute_diffuse(hit, light)
            color += compute_specular(hit, view_dir, light)

    # Add ambient term
    color += hit.obj.material.ambient_color
    return color

	function shade_hit(scene, hit, ray, depth):
    local_color = compute_lighting(scene, hit, ray.dir)
    reflected_color = compute_reflection(scene, hit, ray, depth)
    cos_theta = -dot(ray.dir, hit.normal)
    final_color = fresnel_blend(local_color, reflected_color, hit.obj.material, cos_theta)
    return final_color


*/

t_vec4 compute_lighting(struct s_rt_scene *scene, t_hit hit, t_line ray)
{
	t_vec4 colour = {0, 0, 0};
	unsigned int	i;

	(void)ray;
	(void)hit;
	i = -1;
	while (++i < scene->element_count)
	{
		if (scene->elements[i].type == LIGHT)
		{
		//	if (!in_shadow(scene, hit.point, &scene->elements[i]))
		//	{
			//	colour = vec3_add(colour, compute_diffuse(hit, light));
			//	colour = vec3_add(colour, compute_specular(hit, ray, light));
		//	}
		}
	}
	colour = compute_ambient(scene->ambient_light, colour);
	return (colour);
}

t_vec4 shade(struct s_rt_scene *scene, t_hit *hit, t_line ray, int depth)
{
    t_vec4 local_color = compute_lighting(scene, *hit, ray); 
	(void)depth;
  //  t_vec4 reflected_color = compute_reflection(scene, hit, ray, depth);
 //   t_vec4 final_color = fresnel_blend(local_color, reflected_color, hit->obj->material);
    return local_color;
}