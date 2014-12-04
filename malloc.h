/*
** malloc.h for malloc in /home/bovier_m/rendu/PSU_2013_malloc
**
** Made by Maxence Bovier-Lapierre
** Login   <bovier_m@epitech.net>
**
** Started on  Fri Feb 14 14:35:42 2014 Maxence Bovier-Lapierre
** Last update Fri Feb 14 14:35:44 2014 Maxence Bovier-Lapierre
*/

#ifndef MALLOC_H_
# define MALLOC_H_

/*
 * Includes
 */
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

/*
 * Structures
 */
typedef struct s_bloc	t_bloc;
struct		s_bloc
{
  size_t	isFree;
  size_t	size;
  t_bloc	*next;
  t_bloc	*prev;
  void		*data;
};

typedef	struct s_header	t_header;
struct		s_header
{
  size_t	page;
  t_bloc	*first;
  t_bloc	*end;
  void		*breakPtr;
};

/*
 * Defines
 */
#define H_BLOC		sizeof(t_bloc)
#define H_MALLOC	sizeof(t_header)
#define	SIZE_ADDR	sizeof(void*)
#define FREE		'F'
#define BUSY		'B'
#define SIZE_MIN	48 - H_BLOC
#define aligne4(c)	(((c) - 1) / SIZE_ADDR * SIZE_ADDR + SIZE_ADDR)
#define BASE10		"0123456789"
#define BASE16		"0123456789abcdef"

/*
 * thread.c
 */
void		*malloc(size_t size);
void		free(void *ptr);
void		*calloc(size_t nb, size_t size);
void		*realloc(void *ptr, size_t size);

/*
 * malloc.c
 */
void		*_malloc(size_t size);
t_bloc		*init_memory(size_t size);
t_bloc		*find_bloc(size_t size);
t_bloc		*alloc_bloc(t_bloc *bloc, size_t size);
int		new_page(size_t size);

/*
 * free.c
 */
void		_free(void *ptr);
t_bloc		*update_first(t_bloc *bloc);
t_bloc		*merge_bloc(t_bloc *bloc);
void		check_page(void);

/*
 * realloc.c
 */
void		*_calloc(size_t nb, size_t size);
void		*_realloc(void *ptr, size_t size);
void		malloc_abort(char *s, void *ptr);

/*
 * show_alloc_mem.c
 */
void		show_alloc_mem(void);
void		_putstr(char *str);
void	        _putnbr(size_t nb, char *base);
void		_putaddr(void *addr);

#endif /* !_MALLOC_H_ */
