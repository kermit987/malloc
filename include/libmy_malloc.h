/*
** libmy_malloc.h for  in /home/karmes_l/Projets/tek2/Systeme_Unix-Memoire/PSU_2015_malloc/include
** 
** Made by Karmes Lionel
** Login   <karmes_l@epitech.net>
** 
** Started on  Mon Jan 25 17:41:15 2016 Karmes Lionel
** Last update Sun Feb 14 13:19:22 2016 Karmes Lionel
*/

#ifndef LIBMY_MALLOC_H_
# define LIBMY_MALLOC_H_

# include <unistd.h>
# include <stddef.h>
# include <pthread.h>

# define NOT_FREE (0)
# define SIZEINT sizeof(int)
# define alignInt(x) (SIZEINT * ((x) / SIZEINT + ((x) % SIZEINT == 0 ? 0 : 1)))
# define METADATA_SIZE (sizeof(t_metaData) - sizeof(char *))

typedef struct			s_metaData
{
  size_t			size;
  struct s_metaData		*next;
  struct s_metaData		*prev;
  int				free;
  int				magic;
  char				data[1];
}				t_metaData;

typedef struct			s_controlMetaData
{
  t_metaData			*first;
  t_metaData			*last;
}				t_controlMetaData;

extern t_controlMetaData	*g_control;
extern pthread_mutex_t		g_mutex;

void				show_alloc_mem();
void				free(void *);
void				free_next(t_metaData *);
void				*realloc(void *, size_t);
void				*realloc_next(size_t, unsigned int, void *);
void				split(t_metaData *, size_t);
void				merge(t_metaData **);
void				*malloc(size_t);
int				malloc_next(size_t);
t_metaData			*data_valid(void *);

#endif /* !LIBMY_MALLOC_H_ */
