#ifndef ARENA_H

#define ARENA_H

#include <stddef.h>

typedef struct Arena Arena;

void *m_align_alloc(size_t capacity);
void m_align_free(void *ptr);
void *m_align_realloc(void *ptr, size_t old_size, size_t new_size);

Arena *arena_init(size_t capacity);
void *arena_alloc(Arena *arena, size_t size);
void arena_free(Arena **arena);
void arena_reset(Arena **arena);

#endif
