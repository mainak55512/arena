#include <stdio.h>
#include <stdlib.h>

typedef struct Arena {
	void *region;
	size_t size;
	size_t capacity;
	struct Arena *next;
} Arena;

Arena *arena_init(size_t capacity) {
	Arena *arena = (Arena *)malloc(sizeof(Arena));
	void *data = malloc(capacity);
	if (arena == NULL || data == NULL) {
		fprintf(stderr, "Fatal: Failed to allocate arena");
		abort();
	}
	arena->region = data;
	arena->capacity = capacity;
	arena->size = 0;
	arena->next = NULL;
	return arena;
}

void *arena_alloc(Arena *arena, size_t size) {
	Arena *current_arena = arena;
	void *data = NULL;
	if (current_arena->size + size <= current_arena->capacity) {
		data = (char *)current_arena->region + current_arena->size;
		current_arena->size += size;
	} else {
		if (current_arena->next != NULL) {
			current_arena = current_arena->next;
			data = arena_alloc(current_arena, size);
		} else {
			Arena *new_arena = NULL;
			if (current_arena->capacity < size) {
				new_arena = arena_init(size);
			} else {
				new_arena = arena_init(arena->capacity);
			}
			current_arena->next = new_arena;
			data = arena_alloc(new_arena, size);
		}
	}
	return data;
}

void arena_free(Arena *arena) {
	if (arena->next != NULL) {
		arena_free(arena->next);
	}
	free(arena->region);
	free(arena);
	return;
}
