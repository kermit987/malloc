/*
** free.c for  in /home/karmes_l/Projets/tek2/Systeme_Unix-Memoire/PSU_2015_malloc/test/lib
** 
** Made by Karmes Lionel
** Login   <karmes_l@epitech.net>
** 
** Started on  Wed Jan 27 11:16:00 2016 Karmes Lionel
** Last update Sun Feb 14 13:17:37 2016 Karmes Lionel
*/

#include "libmy_malloc.h"

t_metaData	*data_valid(void *data)
{
  t_metaData	*source;

  if (!data || data < (void *)g_control->first + METADATA_SIZE ||
      data >= sbrk(0))
    return (NULL);
  source = data - METADATA_SIZE;
  if (source->free == NOT_FREE && source->magic == 1234)
    return (source);
  return (NULL);
}

void	merge(t_metaData **source)
{
  if (*source && (*source)->free)
    {
      if ((*source)->prev && (*source)->prev->free)
	*source = (*source)->prev;
      while ((*source)->next && (*source)->next->free)
	{
	  (*source)->size += (*source)->next->size + METADATA_SIZE;
	  (*source)->next = (*source)->next->next;
	  if ((*source)->next != NULL)
	    (*source)->next->prev = *source;
	  else
	    g_control->last = (*source);
	}
    }
}

void		free_next(t_metaData *source)
{
  source->free = !NOT_FREE;
  merge(&source);
  if (source->next == NULL &&
      source->size + METADATA_SIZE >= (unsigned int)getpagesize())
    {
      if (source->prev)
	{
	  source->prev->next = NULL;
	  g_control->last = source->prev;
	  sbrk(-source->size - METADATA_SIZE);
	}
      else
	{
	  sbrk(-source->size - METADATA_SIZE - sizeof(t_controlMetaData));
	  g_control = NULL;
	}
    }
}

void		free(void *data)
{
  t_metaData	*source;

  pthread_mutex_lock(&g_mutex);
  if ((source = data_valid(data)) != NULL)
    free_next(source);
  pthread_mutex_unlock(&g_mutex);
}
