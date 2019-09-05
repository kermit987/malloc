/*
** show_alloc_mem.c for  in /home/loofat_s/rendu/PSU_2015_malloc/steven_test/test2
**
** Made by steven loofat
** Login   <loofat_s@epitech.net>
**
** Started on  Thu Feb  4 12:06:54 2016 steven loofat
** Last update Sun Feb 14 12:51:05 2016 Steven Loo Fat
*/

#include "libmy_malloc.h"
#include <stdio.h>

void	show_alloc_mem()
{
  t_metaData	*tmp;

  printf("break : %p\n", sbrk(0));
  if (g_control != NULL)
    {
      tmp = g_control->first;
      while (tmp != NULL)
	{
	  if (tmp->free == NOT_FREE)
	    printf("%p - %p : %u bytes\n", tmp->data, tmp->data + tmp->size,
		   (unsigned int)tmp->size);
	  tmp = tmp->next;
	}
    }
}
