#ifndef PHILOSOPHERS_BONUS_H

# define PHILOSOPHERS_BONUS_H

# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <signal.h>
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

# define SEM_FORKS		"/forks"
# define SEM_SIMULATION	"/simulation"
# define SEM_DEATH		"/death"
# define SEM_WRITE		"/write"
# define SEM_EAT		"/eat"

typedef struct s_data
{
	int				id;
	pid_t			*pids;

	int				nbr_philos;  // arg1
	int				time_to_die;  // arg2
	int				time_to_eat;  // arg3
	int				time_to_sleep;  // arg4
	int				nbr_of_meals;  // arg5
	int				meals;
	time_t			time_of_last_meal;  // time when data last eat im ms
	time_t			start_time;
	int				dead;

	sem_t			*forks;
	sem_t			*simulation;
	sem_t			*write_sem;
	sem_t			*death_sem;
	sem_t			*eat_sem;

}					t_data;


/*
**  main.c
*/

int			main(int argc, char **argv);

/*
**  processing.c
*/

int		start_count_monitor(t_data *data);

int		start_processes(t_data *data);

void	*life_cycle(t_data *data);

void	*monitor(void *datum);


/*
**  events.c
*/

void	take_forks(t_data *data);

void	eating(t_data *data);

void	sleeping(t_data *data);

/*
**  ft_atoi.c
*/

int		ft_atoi(const char *str);

/*
**  init.c
*/

int			init_data(int argc, char **argv, t_data *data);

int			init_semaphores(t_data *data);

int			init(int argc, char **argv, t_data *data);

/*
**  message.c
*/

void		display_message(t_data *data, int type);

/*
**  utils_libft.c
*/

int			ft_strncmp(const char *s1, const char *s2, long n);

int			ft_isdigit(int c);

long		ft_strlen(char *str);

void		ft_putnbr_fd(int n, int fd);

/*
**  utils_data.c
*/

int			check_arguments(int argc);

long		current_time(void);

void		ft_usleep(int ms);

void		*monitor_count(void *datum);


#endif
