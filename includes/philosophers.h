#ifndef PHILOSOPHERS_H

# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>


typedef struct s_philo
{
	int				id;
	int				nbr_of_meals;  // each time philo eats -> nbr_of_meals++
	time_t			time_of_last_meal;  // time when philo last eat im ms
	time_t			limit_of_life;  // when time_of_last_meal > limit_of_life

	pthread_mutex_t	*fork1;
	pthread_mutex_t	*fork2;
}					t_philo;

typedef struct s_data
{
	int				nbr_philos;  // arg1
	int				time_to_die;  // arg2
	int				time_to_eat;  // arg3
	int				time_to_sleep;  // arg4
	int				nbr_of_meals;  // arg5

	pthread_mutex_t	*forks;
	pthread_t		*tids;  // IDs of threads

	t_philo			*philosophers;
}					t_data;


/*
**  main.c
*/

void		run_threads(t_data *data);

void		*processing(void *data);

/*
**  init.c
*/

void		init_data(t_data *data, int argc, char **argv);

void		init_forks(t_data *data);

void		init_philosophers(t_data *data);

/*
**  things.c
*/

void	take_forks(t_philo *philo);

void	eating(t_philo *philo);

void	thinking(t_philo *philo);

void	sleeping(t_philo *philo);

/*
**  utils.c
*/

void		terminate(const char *error);

int			ft_strncmp(const char *s1, const char *s2, size_t n);

int			ft_isdigit(int c);

/*
**  ft_atoi.c
*/

int			ft_atoi(const char *str);

#endif
