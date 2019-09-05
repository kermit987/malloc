/*
** realloc.c for  in /home/karmes_l/Projets/tek2/Systeme_Unix-Memoire/PSU_2015_malloc
**
** Made by Karmes Lionel
** Login   <karmes_l@epitech.net>
**
** Started on  Wed Jan 27 18:46:00 2016 Karmes Lionel
** Last update Sun Feb 14 15:38:40 2016 Karmes Lionel
*/

#include "libmy_malloc.h"

void		*realloc_next(size_t size, unsigned int tmp_size, void *data)
{
  void		*destination;
  unsigned int	i;

  i = 0;
  if ((destination = malloc(size)) == NULL)
    return (NULL);
  while (i * sizeof(int) < tmp_size && i * sizeof(int) < size)
    {
      ((int *)destination)[i] = ((int *)data)[i];
      ++i;
    }
  free(data);
  return (destination);
}

void		*realloc(void *data, size_t size)
{
  t_metaData	*source;
  unsigned int	tmp_size;

  size = alignInt(size);
  if (data == NULL || (source = data_valid(data)) == NULL)
    return (malloc(size));
  tmp_size = source->size;
  pthread_mutex_lock(&g_mutex);
  source->free = !NOT_FREE;
  if (source->prev && source->prev == NOT_FREE)
    merge(&source);
  source->free = NOT_FREE;
  if (source->size >= size + sizeof(t_metaData) + sizeof(int))
    split(source, size);
  pthread_mutex_unlock(&g_mutex);
  if (source->size >= size)
    return (source->data);
  else
    return (realloc_next(size, tmp_size, data));
}
