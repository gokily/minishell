#ifndef FT_ENV_H
# define FT_ENV_H

# define ENVFLAG "Ciu"

typedef struct			s_varlst
{
	struct s_pathlst	*next;
	char				*var;
}						t_varlst;

typedef struct		s_env
{
	int				flag;
	struct s_varlst	*varlst;
	char			*dir;
}


#endif