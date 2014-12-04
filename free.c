/*
** free.c for malloc in /home/bovier_m/rendu/PSU_2013_malloc
**
** Made by Maxence Bovier-Lapierre
** Login   <bovier_m@epitech.net>
**
** Started on  Fri Feb 14 14:34:49 2014 Maxence Bovier-Lapierre
** Last update Fri Feb 14 14:34:52 2014 Maxence Bovier-Lapierre
*/

#include "malloc.h"

extern t_header		*header;

void		_free(void *ptr)
{
  t_bloc	*bloc;

  if (ptr == NULL)
    return;
  if ((ptr < (void*)header || ptr >= header->breakPtr))
    malloc_abort("free(): invalid pointer1: ", ptr - H_BLOC);
  bloc = (t_bloc*)(ptr - H_BLOC);
  if (bloc->data != (void*)bloc + H_BLOC)
    malloc_abort("free(): invalid pointer2: ", ptr - H_BLOC);
  if (bloc->isFree == FREE)
    malloc_abort("free(): Already free pointer3: ", ptr - H_BLOC);
  bloc->isFree = FREE;
  if (bloc->prev != NULL && bloc->prev->isFree == FREE)
    {
      bloc = bloc->prev;
      merge_bloc(bloc);
    }
  if (bloc->next != header->breakPtr && bloc->next->isFree == FREE)
    merge_bloc(bloc);
  if (ptr < (void*)header->first)
    header->first = bloc;
  if (ptr - H_BLOC == (void*)header->end)
    check_page();
}

void		check_page(void)
{
  t_bloc	*bloc;
  size_t	pageDel;
  size_t	sizeRest;

  bloc = header->end;
  if (bloc->size + H_BLOC >= header->page)
    {
      pageDel = (bloc->size + H_BLOC) / header->page;
      sizeRest = (bloc->size + H_BLOC) % header->page;
      if (sizeRest >= H_BLOC + SIZE_MIN)
	bloc->size = sizeRest - H_BLOC;
      else if (sizeRest == 0)
	header->end = bloc->prev;
      else
	{
	  header->end = bloc->prev;
	  header->end->size += sizeRest - H_BLOC;
	}
      header->breakPtr -= pageDel * header->page;
      header->end->next = header->breakPtr;
      brk(header->breakPtr);
    }
}

t_bloc		*merge_bloc(t_bloc *bloc)
{
  t_bloc	*bloc2;

  bloc2 = bloc->next;
  bloc->size += H_BLOC + bloc2->size;
  bloc->next = bloc2->next;
  if (bloc2->next != header->breakPtr)
    bloc2->next->prev = bloc;
  header->first = (bloc2 == header->first) ? bloc : header->first;
  header->end = (bloc2 == header->end) ? bloc : header->end;
  return bloc;
}

t_bloc		*update_first(t_bloc *bloc)
{
  while (bloc != header->breakPtr)
    {
      if (bloc->isFree == FREE)
	break;
      bloc = bloc->next;
    }
  return bloc;
}
