#ifndef PHILOSOPHERS_BONUS_H

# define PHILOSOPHERS_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <semaphore.h>

# define TYPE_FORK		1
# define TYPE_EAT		2
# define TYPE_SLEEP		3
# define TYPE_THINK		4
# define TYPE_OVER		5
# define TYPE_DIED		6

struct s_data;

typedef struct s_philo
{
	int				id;
	int				dead;
	int				nbr_of_meals;  // each time philo eats -> nbr_of_meals++
	time_t			time_of_last_meal;  // time when philo last eat im ms
	time_t			limit_of_life;  // when time_of_last_meal > limit_of_life
	time_t			start_time;

	sem_t			*death_sem;

	struct s_data	*data;
}					t_philo;

typedef struct s_data
{
	int				nbr_philos;  // arg1
	int				time_to_die;  // arg2
	int				time_to_eat;  // arg3
	int				time_to_sleep;  // arg4
	int				nbr_of_meals;  // arg5

	sem_t			*forks;
	sem_t			*write_sem;

	t_philo			*philosophers;
}					t_data;


/*
**  main.c
*/

int			main(int argc, char **argv);

/*
**  events.c
*/

void	take_forks(t_philo *philo);

void	eating(t_philo *philo);

void	thinking(t_philo *philo);

void	sleeping(t_philo *philo);

/*
**  ft_atoi.c
*/

int		ft_atoi(const char *str);

/*
**  init.c
*/

int			init_data(int argc, char **argv, t_data *data);

int			init_forks(t_data *data);

int			init_philosophers(t_data *data);

int			init(int argc, char **argv, t_data *data);

/*
**  message.c
*/

void		display_message(t_philo *philo, int type);

/*
**  utils_libft.c
*/

int			ft_strncmp(const char *s1, const char *s2, long n);

int			ft_isdigit(int c);

long		ft_strlen(char *str);

void		ft_putnbr_fd(int n, int fd);

/*
**  utils_philo.c
*/

int			check_arguments(int argc);

long		current_time(void);

void		ft_usleep(int ms);

int			count_meals(t_philo *philos);

#endif
