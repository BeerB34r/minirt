/* ************************************************************************** */
/*                                                                            */
/*                                                            ::::::::        */
/*   minirt_declarations.h                                   :+:    :+:       */
/*                                                          +:+               */
/*   By: mde-beer <mde-beer@student.codam.nl>              +#+                */
/*                                                        +#+                 */
/*   Created: 2025/09/18 16:49:55 by mde-beer            #+#    #+#           */
/*   Updated: 2025/09/23 18:16:04 by mde-beer            ########   odam.nl   */
/*                                                                            */
/*   —————No norm compliance?——————                                           */
/*   ⠀⣞⢽⢪⢣⢣⢣⢫⡺⡵⣝⡮⣗⢷⢽⢽⢽⣮⡷⡽⣜⣜⢮⢺⣜⢷⢽⢝⡽⣝                                           */
/*   ⠸⡸⠜⠕⠕⠁⢁⢇⢏⢽⢺⣪⡳⡝⣎⣏⢯⢞⡿⣟⣷⣳⢯⡷⣽⢽⢯⣳⣫⠇                                           */
/*   ⠀⠀⢀⢀⢄⢬⢪⡪⡎⣆⡈⠚⠜⠕⠇⠗⠝⢕⢯⢫⣞⣯⣿⣻⡽⣏⢗⣗⠏⠀                                           */
/*   ⠀⠪⡪⡪⣪⢪⢺⢸⢢⢓⢆⢤⢀⠀⠀⠀⠀⠈⢊⢞⡾⣿⡯⣏⢮⠷⠁⠀⠀⠀                                           */
/*   ⠀⠀⠀⠈⠊⠆⡃⠕⢕⢇⢇⢇⢇⢇⢏⢎⢎⢆⢄⠀⢑⣽⣿⢝⠲⠉⠀⠀⠀⠀                                           */
/*   ⠀⠀⠀⠀⠀⡿⠂⠠⠀⡇⢇⠕⢈⣀⠀⠁⠡⠣⡣⡫⣂⣿⠯⢪⠰⠂⠀⠀⠀⠀                                           */
/*   ⠀⠀⠀⠀⡦⡙⡂⢀⢤⢣⠣⡈⣾⡃⠠⠄⠀⡄⢱⣌⣶⢏⢊⠂⠀⠀⠀⠀⠀⠀                                           */
/*   ⠀⠀⠀⠀⢝⡲⣜⡮⡏⢎⢌⢂⠙⠢⠐⢀⢘⢵⣽⣿⡿⠁⠁⠀⠀⠀⠀⠀⠀⠀                                           */
/*   ⠀⠀⠀⠀⠨⣺⡺⡕⡕⡱⡑⡆⡕⡅⡕⡜⡼⢽⡻⠏⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀                                           */
/*   ⠀⠀⠀⠀⣼⣳⣫⣾⣵⣗⡵⡱⡡⢣⢑⢕⢜⢕⡝⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀                                           */
/*   ⠀⠀⠀⣴⣿⣾⣿⣿⣿⡿⡽⡑⢌⠪⡢⡣⣣⡟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀                                           */
/*   ⠀⠀⠀⡟⡾⣿⢿⢿⢵⣽⣾⣼⣘⢸⢸⣞⡟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀                                           */
/*   ⠀⠀⠀⠀⠁⠇⠡⠩⡫⢿⣝⡻⡮⣒⢽⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀                                           */
/*   ——————————————————————————————                                           */
/* ************************************************************************** */

#ifndef MINIRT_DECLARATIONS_H
# define MINIRT_DECLARATIONS_H

# include <stdint.h> // required for prototyping s_rgba.hex
# include <stdbool.h> // required for prototyping s_rt_scene

enum e_element_type
{
	AMBIENT_LIGHTING = 0,
	CAMERA,
	LIGHT,
	SPHERE,
	PLANE,
	CYLINDER,
	SUPERQUADRIC,
	TRIANGLE,
	STLFILE,
	UNDEFINED
};
//	general constructs

/**
 * struct for conveniently type punning over a 32bit integer to 4x8bit RGBA
 * values
 */
struct s_rgba
{
	union
	{
		uint32_t	hex; //< Full 32 bit representation of a given RGBA value
		struct
		{
			char	r; //< red channel
			char	g; //< green channel
			char	b; //< blue channel
			char	a; //< alpha channel
		};
	};
};

/**
 *	point in 𝐑³ space 
 */
struct s_vec3
{
	double	x;
	double	y;
	double	z;
};

//	elements of a scene

struct s_rt_element_ambient_light
{
	double			ratio;
	struct s_rgba	color;
};
# define AMBIENT_LIGHTING_FIELDS 2

struct s_rt_element_camera
{
	struct s_vec3	pos;
	struct s_vec3	orientation;
	int				fov;
};
# define CAMERA_FIELDS 3

struct s_rt_element_light
{
	struct s_vec3	pos;
	double			brightness;
	struct s_rgba	color;
};
# define LIGHT_FIELDS 3

struct s_rt_element_sphere
{
	struct s_vec3	pos;
	double			radius;
	struct s_rgba	color;
};
# define SPHERE_FIELDS 3

struct s_rt_element_plane
{
	struct s_vec3	pos;
	struct s_vec3	normal;
	struct s_rgba	color;
};
# define PLANE_FIELDS 3

struct s_rt_element_cylinder
{
	struct s_vec3	pos;
	struct s_vec3	axis;
	double			radius;
	double			height;
	struct s_rgba	color;
};
# define CYLINDER_FIELDS 5

struct s_rt_element_triangle
{
	struct s_vec3	normal; // precomputed, not given by user
	struct s_vec3	v1;
	struct s_vec3	v2;
	struct s_vec3	v3;
	struct s_rgba	color;
	uint16_t		attr; // only relevant for stlfile derived tris
};
# define TRIANGLE_FIELDS 4

struct s_rt_element_stlfile
{
	uint8_t							header[80];
	uint32_t						tri_count;
	struct s_rt_element_triangle	*triangles;
};
# define STLFILE_FIELDS 1

struct s_rt_element_superquadric
{
	struct s_vec3	pos;
	double			r;
	double			s;
	double			t;
	double			a;
	double			b;
	double			c;
	struct s_rgba	color;
};
# define SUPERQUADRIC_FIELDS 8

typedef struct s_rt_element
{
	enum e_element_type	type;
	union
	{
		struct s_rt_element_ambient_light	ambient_light;
		struct s_rt_element_camera			camera;
		struct s_rt_element_light			light;
		struct s_rt_element_sphere			sphere;
		struct s_rt_element_plane			plane;
		struct s_rt_element_cylinder		cylinder;
		struct s_rt_element_triangle		triangle;
		struct s_rt_element_stlfile			stlfile;
		struct s_rt_element_superquadric	superquadric;
	};
}	t_element;

typedef struct s_rt_scene
{
	bool								ambient_light_defined;
	struct s_rt_element_ambient_light	ambient_light;
	bool								camera_defined;
	struct s_rt_element_camera			camera;
	bool								light_defined;
	struct s_rt_element_light			light;
	unsigned int						element_count;
	struct s_rt_element					*elements;
}	t_scene;

typedef struct s_element_identifier
{
	char	*name;
	int		(*func)(char **, struct s_rt_scene *);
}	t_element_id;

#endif // MINIRT_DECLARATIONS_H
