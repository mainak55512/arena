#ifndef ARENA_H

#define ARENA_H

#include <stddef.h>

typedef struct Arena Arena;
typedef struct Pool {
	Arena **pool;
	size_t size;
} Pool;

Arena *arena_init(size_t capacity);
void *arena_alloc(Arena *arena, size_t size);
void arena_free(Arena **arena);
Pool *create_arena_pool();
Arena *arena_pool_init(Pool *pool, size_t capacity);
void *arena_pool_alloc(Arena *arena, size_t size);
void arena_pool_free(Pool *pool, Arena **arena);
void arena_pool_destroy(Pool *pool);
#endif
