my_malloc
=========

Recoding of the malloc function from the libc

Functionnality
--------------

  * Provide a dynamic library with malloc(), realloc(), calloc() and free()
  * Implements First Fit algorithm, Spliting blocks, Merging contiguous blocks
  * Thread safe


Examples
--------

```
LD_PRELOAD=/path/to/library/libmy_malloc.sp your_command
```
