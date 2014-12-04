/*
** show_alloc_mem.c for malloc in /home/bovier_m/rendu/PSU_2013_malloc
**
** Made by Maxence Bovier-Lapierre
** Login   <bovier_m@epitech.net>
**
** Started on  Fri Feb 14 14:36:45 2014 Maxence Bovier-Lapierre
** Last update Fri Feb 14 14:36:47 2014 Maxence Bovier-Lapierre
*/

#include "malloc.h"

extern t_header	*header;

void		show_alloc_mem(void)
{
  t_bloc        *bloc;

  bloc = (t_bloc*)((void*)header + H_MALLOC);
  _putstr("break : ");
  _putaddr(header->breakPtr);
  _putstr("\n");
  while (bloc != header->breakPtr)
    {
      _putaddr((void*)bloc + H_BLOC);
      _putstr(" - ");
      _putaddr((void*)bloc->next);
      _putstr(" : ");
      _putnbr(bloc->size, BASE10);
      _putstr(" octets\n");
      bloc = bloc->next;
    }
}

void		_putstr(char *str)
{
  int		i;

  i = 0;
  while (str[i++])
    ;
  write(1, str, i);
}

void		_putnbr(size_t nb, char *base)
{
  if (nb > 0)
    _putnbr(nb / strlen(base), base);
  write(1, &base[nb % strlen(base)], 1);
}

void		_putaddr(void *addr)
{
  if (addr)
    {
      _putstr("0x");
      _putnbr((size_t)&addr, BASE16);
    }
  else
    _putstr("(nil)");
}
