/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minirt_declarations.h                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: mde-beer <mde-beer@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/09/18 16:49:55 by mde-beer      #+#    #+#                 */
/*   Updated: 2025/12/12 11:26:26 by alkuijte      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

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
# include <MLX42.h> // required for uv

# define DEFAULT_AMBI_REFLECTIVITY 0.3f
# define DEFAULT_DIFF_REFLECTIVITY 0.5f
# define DEFAULT_SPEC_REFLECTIVITY 0.8f
# define DEFAULT_ABSO_REFLECTIVITY 0.1f
# define DEFAULT_SHININESS		   0.8f
# define EXPOSURE				   1.5f
# define MAX_DEPTH				   250
# define BUMP_STRENGTH			   2.8f

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
			unsigned char	r; //< red channel
			unsigned char	g; //< green channel
			unsigned char	b; //< blue channel
			unsigned char	a; //< alpha channel
		};
	};
};

/**
 *	point in 𝐑³ space 
 */
typedef union u_vec3
{
	double __attribute__	((vector_size(sizeof(double)*4)))	v;
	double														a[4];
	struct
	{
		double		x;
		double		y;
		double		z;
		double		w; // unused for the most part
	};
}	t_vec3;

typedef t_vec3	t_norm;
typedef t_vec3	t_vec4;
typedef t_vec3	t_vec2;

typedef struct u_uv
{
	double	u;
	double	v;
	t_vec3	t;
	t_vec3	b;
}	t_uv;

typedef union u_tuple
{
	uint32_t	a[2];
	struct
	{
		uint32_t	x;
		uint32_t	y;
	};
}	t_tuple;

typedef struct s_line
{
	t_vec3	origin;
	t_vec3	dir;
}	t_line;

typedef struct s_hit
{
	t_vec3				point;
	t_vec3				normal;
	t_vec3				shading_normal;
	t_line				ray;
	double				t;
	struct s_rt_element	*obj;
	t_uv				uv;
}	t_hit;

//	elements of a scene

struct s_rt_element_ambient_light
{
	double			ratio;
	struct s_rgba	colour;
};
# define AMBIENT_LIGHTING_FIELDS 2

struct s_rt_element_camera
{
	t_vec3			pos;
	t_norm			orientation;
	int				fov;
};
# define CAMERA_FIELDS 3

typedef struct s_rt_element_light
{
	t_vec3			pos;
	double			brightness;
	struct s_rgba	colour;
}	t_rt_element_light;
# define LIGHT_FIELDS 3

typedef struct s_rt_element_sphere
{
	t_vec3			pos;
	double			radius;
	struct s_rgba	colour;
}	t_rt_element_sphere;
# define SPHERE_FIELDS 3

typedef struct s_rt_element_plane
{
	t_vec3			pos;
	t_norm			normal;
	struct s_rgba	colour;
}	t_rt_element_plane;
# define PLANE_FIELDS 3

typedef struct s_rt_element_cylinder
{
	t_vec3			pos;
	t_norm			axis;
	double			radius;
	double			height;
	struct s_rgba	colour;
}	t_rt_element_cylinder;
# define CYLINDER_FIELDS 5

typedef struct s_rt_triangle_uv
{
	t_vec2			uv1;
	t_vec2			uv2;
	t_vec2			uv3;
	t_vec3			e1;
	t_vec3			e2;
	double			du1;
	double			dv1;
	double			du2;
	double			dv2;
	double			r;
}	t_rt_triangle_uv;

typedef struct s_rt_element_triangle
{
	t_norm				normal; // precomputed, not given by user
	t_vec3				v1;
	t_vec3				v2;
	t_vec3				v3;
	t_rt_triangle_uv	tr_uv;
	struct s_rgba		colour;
	uint16_t			attr; // only relevant for stlfile derived tris
}	t_rt_element_triangle;
# define TRIANGLE_FIELDS 4
# define PIXEL_STL_TRI_FALLBACK 0xFFBC8DFF

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
	TOROID
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
	struct s_rgba		colour;
};
# define SUPERQUADRIC_FIELDS 12

typedef struct s_material
{
	struct s_rgba	colour;
	float			spec_reflectivity;
	float			diff_reflectivity;
	float			ambi_reflectivity;
	float			abso_reflectivity;
	float			shininess;
	mlx_texture_t	*texture;
	mlx_texture_t	*bump_map;
}	t_material;

typedef int		(*t_intersect_fn)(t_line ray,
			const void *data, double *t, t_uv *uv);

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
	struct s_material	material;
	t_intersect_fn		intersect;
	const void			*data;
}	t_element;

typedef struct s_rt_scene
{
	bool								ambient_light_defined;
	struct s_rt_element_ambient_light	ambient_light;
	bool								camera_defined;
	struct s_rt_element_camera			camera;
	unsigned int						light_count;
	struct s_rt_element_light			*lights;
	unsigned int						element_count;
	struct s_rt_element					*elements;
}	t_scene;

typedef struct s_element_identifier
{
	char	*name;
	int		(*func)(char **, struct s_rt_scene *);
}	t_element_id;

typedef struct s_tri_work
{
	t_vec3	e1;
	t_vec3	e2;
	t_vec3	p;
	t_vec3	q;
	double	u;
	double	v;
	double	det;
	double	inv_det;
}	t_tri_work;

typedef struct s_cyl_work
{
	t_vec3	axis;
	t_vec3	delta;
	t_vec3	a;
	t_vec3	b;
	t_vec3	p;
	t_vec3	v;
	double	a_coef;
	double	b_coef;
	double	c_coef;
	double	disc;
	double	t_side;
	double	t_bottom;
	double	t_top;
	double	denom;
	double	t_cap;
	double	t_final;
	double	d;
	t_uv	side_uv;
	t_uv	top_cap_uv;
	t_uv	bottom_cap_uv;
}	t_cyl_work;

typedef struct s_shade_input
{
	t_rt_element_light	light;
	t_vec4				base_colour;
	t_material			mat;
	t_vec3				view_dir;
	t_vec3				n;
	t_vec3				l;
	double				dot_ln;
}	t_shade_input;

typedef struct s_trace_work
{
	struct s_rt_scene	*scene;
	t_line				ray;
	int					depth;
	t_vec4				bg;
	t_vec4				colour;
	t_hit				hit;
}	t_trace_work;

#endif // MINIRT_DECLARATIONS_H
