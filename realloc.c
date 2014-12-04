/*
** realloc.c for malloc in /home/bovier_m/rendu/PSU_2013_malloc
**
** Made by Maxence Bovier-Lapierre
** Login   <bovier_m@epitech.net>
**
** Started on  Fri Feb 14 14:36:01 2014 Maxence Bovier-Lapierre
** Last update Fri Feb 14 14:36:02 2014 Maxence Bovier-Lapierre
*/

#include "malloc.h"

extern t_header		*header;
extern pthread_mutex_t	mutex;

void		*_calloc(size_t nb, size_t size)
{
  void		*ptr;

  if (!nb || !size)
    return NULL;
  ptr = _malloc(nb * size);
  memset(ptr, 0, nb * size);
  return ptr;
}

void		*realloc_m(t_bloc *bloc, size_t size)
{
  void		*ptr;

  ptr = alloc_bloc(bloc, size);
  return ptr + H_BLOC;
}

void		*realloc_p(t_bloc *bloc, size_t size)
{
  void		*ptr;

  ptr = _malloc(size);
  memcpy(ptr, (void*)bloc + H_BLOC, bloc->size);
  _free((void*)bloc + H_BLOC);
  return ptr;
}

void		*_realloc(void *ptr, size_t size)
{
  t_bloc	*bloc;

  if (!ptr)
    return _malloc(size);
  if (!size)
    {
      _free(ptr);
      return NULL;
    }
  if (header == NULL)
    return _malloc(size);
  if (ptr < (void*)header || ptr > header->breakPtr)
    malloc_abort("realloc() : Invalid pointer ", ptr);
  bloc = (t_bloc*)(ptr - H_BLOC);
  if (bloc->data != (void*)bloc + H_BLOC)
    malloc_abort("realloc() : Invalid pointer ", ptr);
  if (size <= bloc->size)
    return realloc_m(bloc, size);
  return realloc_p(bloc, size);
}

void		malloc_abort(char *s, void *ptr)
{
  _putstr(s);
  _putaddr(ptr);
  abort();
}
