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
typedef union u_vec3
{
	double		a[4];
	struct
	{
		double	x;
		double	y;
		double	z;
		double	w; // unused for the most part
	};
}	t_vec3;

typedef t_vec3	t_norm;
typedef t_vec3	t_vec4;

typedef union u_uv
{
	double	a[2];
	struct
	{
		double	u;
		double	v;
	};
}	t_uv;

typedef struct s_line
{
	t_vec3	origin;
	t_norm	normal;
}	t_line;

//	elements of a scene

struct s_rt_element_ambient_light
{
	double			ratio;
	struct s_rgba	color;
};
# define AMBIENT_LIGHTING_FIELDS 2

struct s_rt_element_camera
{
	t_vec3			pos;
	t_norm			orientation;
	int				fov;
};
# define CAMERA_FIELDS 3

struct s_rt_element_light
{
	t_vec3			pos;
	double			brightness;
	struct s_rgba	color;
};
# define LIGHT_FIELDS 3

struct s_rt_element_sphere
{
	t_vec3			pos;
	double			radius;
	struct s_rgba	color;
};
# define SPHERE_FIELDS 3

struct s_rt_element_plane
{
	t_vec3			pos;
	t_norm			normal;
	struct s_rgba	color;
};
# define PLANE_FIELDS 3

struct s_rt_element_cylinder
{
	t_vec3			pos;
	t_norm			axis;
	double			radius;
	double			height;
	struct s_rgba	color;
};
# define CYLINDER_FIELDS 5

struct s_rt_element_triangle
{
	t_norm			normal; // precomputed, not given by user
	t_vec3			v1;
	t_vec3			v2;
	t_vec3			v3;
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

enum e_sq_subtype
{
	ELLIPSOID,
	HYPERBOLOID1,
	HYPERBOLOID2,
	TORUS
};
struct s_rt_element_superquadric
{
	enum e_sq_subtype	subtype;
	t_vec3				pos;
	t_vec4				rot;
	double				e1p;
	double				e1q;
	double				e1;
	double				e2p;
	double				e2q;
	double				e2;
	double				a1;
	double				a2;
	double				a3;
	double				a4;	// TORUS EXCLUSIVE
	double				a;	// TORUS EXCLUSIVE
	struct s_rgba		color;
};
# define SUPERQUADRIC_FIELDS 12

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
