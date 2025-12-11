#ifndef ARENA_H

#define ARENA_H

#include <stddef.h>

typedef struct Arena Arena;

Arena *arena_init(size_t capacity);
void *arena_alloc(Arena *arena, size_t size);
void arena_free(Arena **arena);
#endif
