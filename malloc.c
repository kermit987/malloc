/*
** malloc.c for  in /home/karmes_l/Projets/tek2/Systeme_Unix-Memoire/PSU_2015_malloc
**
** Made by Karmes Lionel
** Login   <karmes_l@epitech.net>
**
** Started on  Mon Jan 25 17:40:18 2016 Karmes Lionel
** Last update Sun Feb 14 13:39:44 2016 Steven Loo Fat
*/

#include "libmy_malloc.h"

t_controlMetaData	*g_control = NULL;
pthread_mutex_t		g_mutex = PTHREAD_MUTEX_INITIALIZER;

t_metaData		*extend_heap(size_t size)
{
  t_metaData		*new;
  unsigned int		size_page;

  if (size > 0)
    {
      size_page = getpagesize() * ((size + METADATA_SIZE - 1)
      				   / getpagesize() + 1);
      if ((new = sbrk(size_page)) == (void *)-1)
	return (NULL);
      new->size = size_page - METADATA_SIZE;
      new->free = NOT_FREE;
      new->magic = 1234;
      new->next = NULL;
      new->prev = g_control->last;
      if (g_control->last)
	g_control->last->next = new;
      g_control->last = new;
      if (new->size >= size + METADATA_SIZE + sizeof(int))
	split(new, size);
    }
  return (new);
}

t_metaData		*findFreeMetaData(size_t size)
{
  t_metaData		*tmp;

  tmp = g_control->first;
  while (tmp && (!tmp->free || tmp->size < size))
    tmp = tmp->next;
  if (tmp)
    tmp->free = NOT_FREE;
  return (tmp);
}

void			split(t_metaData *find, size_t size)
{
  t_metaData		*new;

  new = (t_metaData *)(find->data + size);
  new->size = find->size - size - METADATA_SIZE;
  new->free = !NOT_FREE;
  new->magic = 1234;
  new->next = find->next;
  if (new->next)
    new->next->prev = new;
  new->prev = find;
  if (find->next == NULL)
    g_control->last = new;
  find->next = new;
  find->size = size;
}

t_metaData		*first_malloc(size_t size)
{
  t_metaData		*find;

  if ((g_control = sbrk(sizeof(t_controlMetaData))) == NULL)
    return (NULL);
  g_control->last = NULL;
  find = extend_heap(size);
  g_control->first = g_control->last;
  if (g_control->first && g_control->first->prev)
    g_control->first = g_control->first->prev;
  return (find);
}

void			*malloc(size_t size)
{
  t_metaData		*find;

  pthread_mutex_lock(&g_mutex);
  size = alignInt(size);
  if (g_control != NULL)
    {
      if ((find = findFreeMetaData(size)) != NULL)
	{
	  if (find->size >= size + METADATA_SIZE + sizeof(int))
	    split(find, size);
	}
      else
	find = extend_heap(size);
    }
  else
    find = first_malloc(size);
  pthread_mutex_unlock(&g_mutex);
  return (find ? find->data : NULL);
}
