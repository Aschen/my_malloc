/*
** malloc.c for malloc in /home/bovier_m/rendu/PSU_2013_malloc
**
** Made by Maxence Bovier-Lapierre
** Login   <bovier_m@epitech.net>
**
** Started on  Fri Feb 14 14:35:09 2014 Maxence Bovier-Lapierre
** Last update Fri Feb 14 14:35:11 2014 Maxence Bovier-Lapierre
*/

#include <string.h>
#include "malloc.h"

t_header	*header = NULL;

void		*_malloc(size_t size)
{
  t_bloc	*bloc;

  if (size == 0)
    return NULL;
  size = (size < SIZE_MIN) ? (SIZE_MIN) : (size);
  size = aligne4(size);
  if (header == NULL)
    bloc = init_memory(size);
  else
    bloc = find_bloc(size);
  if (bloc)
    return ((void*)bloc + H_BLOC);
  return NULL;
}

t_bloc		*init_memory(size_t size)
{
  size_t	pageSize;
  size_t	i;
  t_bloc	*bloc;

  pageSize = getpagesize();
  i = 1;
  while ((pageSize * i) < (H_MALLOC + H_BLOC + size))
    i++;
  header = sbrk((intptr_t)((void*)header + pageSize * i));
  header->page = pageSize;
  header->breakPtr = (void*)header + pageSize * i;
  header->end = (void*)header + H_MALLOC;
  bloc = (t_bloc*)((void*)header + H_MALLOC);
  header->first = bloc;
  bloc->size = pageSize * i - H_MALLOC - H_BLOC;
  bloc->isFree = FREE;
  bloc->prev = NULL;
  bloc->next = header->breakPtr;
  bloc->data = (void*)bloc + H_BLOC;
  return alloc_bloc(bloc, size);
}

t_bloc		*alloc_bloc(t_bloc *bloc, size_t size)
{
  t_bloc	*split_bloc;
  void		*ptr;

  ptr = (void*)bloc;
  if (bloc->size >= size + H_BLOC + SIZE_MIN)
    {
      split_bloc = (t_bloc*)(ptr + H_BLOC + size);
      split_bloc->size = bloc->size - (size + H_BLOC);
      split_bloc->isFree = FREE;
      split_bloc->next = bloc->next;
      split_bloc->prev = bloc;
      split_bloc->data = (void*)split_bloc + H_BLOC;
      bloc->size = size;
      if (bloc->next != header->breakPtr)
	bloc->next->prev = split_bloc;
      bloc->next = split_bloc;
      header->end = (header->end == bloc) ? split_bloc : header->end;
      header->first = (header->first == bloc) ? split_bloc : header->first;
    }
  bloc->isFree = BUSY;
  bloc->data = (void*)bloc + H_BLOC;
  if (bloc == header->first)
    header->first = update_first(bloc);
  return bloc;
}

t_bloc		*find_bloc(size_t size)
{
  t_bloc	*bloc;

  if (header->first == NULL)
    {
      if (!(new_page(size)))
	return NULL;
      return alloc_bloc(header->first, size);
    }
  bloc = header->first;
  while (bloc != header->breakPtr)
    {
      if (bloc->size >= (size) && bloc->isFree == FREE)
	return alloc_bloc(bloc, size);
      bloc = bloc->next;
    }
  if (!(new_page(size)))
    return NULL;
  if (header->end->prev->isFree == FREE)
    return alloc_bloc(merge_bloc(header->end->prev), size);
  return alloc_bloc(header->end, size);
}

int		new_page(size_t size)
{
  t_bloc	*bloc;
  int		i;

  i = 1;
  while ((header->page * i) < (H_BLOC + size))
    i++;
  bloc = (t_bloc*)header->breakPtr;
  header->breakPtr += header->page * i;
  if (brk(header->breakPtr))
    return 0;
  bloc->size = header->page * i - H_BLOC;
  bloc->isFree = FREE;
  bloc->next = header->breakPtr;
  bloc->prev = header->end;
  bloc->data = (void*)bloc + H_BLOC;
  header->end = bloc;
  return 1;
}
