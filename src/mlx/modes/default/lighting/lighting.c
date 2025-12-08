/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lighting.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: alkuijte <alkuijte@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/12/04 13:31:52 by alkuijte      #+#    #+#                 */
/*   Updated: 2025/12/08 15:28:54 by alkuijte      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <MLX42.h>
#include <minirt_declarations.h>
#include <minirt_math.h>
#include <minirt_math_superquadrics.h>
#include <minirt_mlx.h>
#include <math.h>
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
    reflected_colour = recursive_default_colour(scene, reflected_ray, depth + 1)

    # 3. Weight by reflectivity
    return reflected_colour * hit.obj.material.reflectivity

function fresnel_blend(local_colour, reflected_colour, material, cos_theta):
    # Compute Fresnel term (Schlick approximation)
    F = fresnel_schlick(cos_theta, material.ior)

    # Weight reflection by Fresnel, local colour by (1 - Fresnel)
    return local_colour * (1 - F) + reflected_colour * F

function compute_diffuse(hit, light):
    L = normalize(light.position - hit.point)  # light direction
    N = normalize(hit.normal)

    # Diffuse intensity = max(0, N · L)
    intensity = max(0, dot(N, L))

    return hit.obj.material.diffuse_colour * light.colour * intensity

function compute_specular(hit, view_dir, light):
    L = normalize(light.position - hit.point)  # light direction
    N = normalize(hit.normal)
    V = normalize(-view_dir)                   # direction to camera

    # Phong model: R = reflect(-L, N)
    R = reflect(-L, N)
    spec_intensity = pow(max(0, dot(R, V)), hit.obj.material.shininess)

    return light.colour * hit.obj.material.specular_colour * spec_intensity

function in_shadow(scene, point, light):
    dir_to_light = normalize(light.position - point)
    dist_to_light = length(light.position - point)
    shadow_ray = { origin: point + dir_to_light * EPSILON, dir: dir_to_light }

    hit_shadow = find_closest_intersection(scene, shadow_ray)
    if hit_shadow exists and hit_shadow.t < dist_to_light:
        return true  # blocked
    return false

function compute_lighting(scene, hit, view_dir):
    colour = vec3(0, 0, 0)
    for light in scene.lights:
        if not in_shadow(scene, hit.point, light):
            colour += compute_diffuse(hit, light)
            colour += compute_specular(hit, view_dir, light)

    # Add ambient term
    colour += hit.obj.material.ambient_colour
    return colour

	function shade_hit(scene, hit, ray, depth):
    local_colour = compute_lighting(scene, hit, ray.dir)
    reflected_colour = compute_reflection(scene, hit, ray, depth)
    cos_theta = -dot(ray.dir, hit.normal)
    final_color = fresnel_blend(local_color, reflected_color, hit.obj.material, cos_theta)
    return final_color


*/


// N = surface normal
// V = direction to camera
// L = direction to light
t_vec4 shade(struct s_rt_scene *scene, t_hit *hit, t_line ray)
{
	t_vec4 colour = {0.0f, 0.0f, 0.0f, 1.0f};
	unsigned int i;
	t_vec3 N = vec3_normalise(hit->normal);
    t_vec3 V = vec3_normalise(vec3_flip(ray.dir));
	t_material material = hit->obj->material;
	t_vec4 material_col = hex_to_vec4(material.colour.hex);
	// AMBIENT
	vec3_add_inplace(&colour, compute_ambient(scene->ambient_light, colour)); // potentially flip
	i = -1;
	while (++i < scene->light_count)
	{
		struct s_rt_element_light light = scene->lights[i];
		t_vec4 light_col = get_light_col(light);
		t_vec3 L = vec3_normalise(vec3_sub(light.pos, hit->point));
		double dotLN = fmaxf(vec3_dot_product(L, N), 0.0f);
		vec3_add_inplace(&colour, compute_diffuse(light_col, material_col, material.diff_reflectivity, dotLN));
		vec3_add_inplace(&colour, compute_specular(light_col, &material, N, V, L, dotLN));
	}
//	clamp_colour(&colour);
	return (colour);
}