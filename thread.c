/*
** thread.c for malloc in /home/bovier_m/rendu/PSU_2013_malloc
**
** Made by Maxence Bovier-Lapierre
** Login   <bovier_m@epitech.net>
**
** Started on  Fri Feb 14 14:34:49 2014 Maxence Bovier-Lapierre
** Last update Fri Feb 14 14:34:52 2014 Maxence Bovier-Lapierre
*/
#include <pthread.h>
#include "malloc.h"

static pthread_mutex_t	mutex_malloc = PTHREAD_MUTEX_INITIALIZER;

void		*malloc(size_t size)
{
  void		*ptr;

  pthread_mutex_lock(&mutex_malloc);
  ptr = _malloc(size);
  pthread_mutex_unlock(&mutex_malloc);
  return ptr;
}

void		*realloc(void *ptr, size_t size)
{
  pthread_mutex_lock(&mutex_malloc);
  ptr = _realloc(ptr, size);
  pthread_mutex_unlock(&mutex_malloc);
  return ptr;
}

void		*calloc(size_t nb, size_t size)
{
  void		*ptr;

  pthread_mutex_lock(&mutex_malloc);
  ptr = _calloc(nb, size);
  pthread_mutex_unlock(&mutex_malloc);
  return ptr;
}

void		free(void *ptr)
{
  pthread_mutex_lock(&mutex_malloc);
  _free(ptr);
  pthread_mutex_unlock(&mutex_malloc);
}
