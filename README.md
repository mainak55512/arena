# Arena Allocator Library

A lightweight arena-style memory allocator for C projects.

## Features
- Simple initialization with a fixed capacity
- Fast linear allocations using a pre-allocated buffer
- One-shot memory release via `arena_free()`
- C89 compatible

## Building & Installing

### Requirements
- CMake (>= 3.10 recommended)
- Clang or GCC

### Build Steps
1. Clone the repository in your project root.
2. In your `CMakeLists.txt` add the following lines:
    ```cmake
    target_include_directories(${PROJECT_NAME} PRIVATE Arena/include)
    add_library(arena STATIC Arena/lib/arena.c)
    target_link_libraries(${PROJECT_NAME} PRIVATE arena)
    ```
3. ```sh
    mkdir build
    cd build
    cmake ..
    make
    ```
## Example

```c
#include <arena.h>
#include <stdio.h>

typedef struct {
	float x;
	float y;
} Point;

void coordinates(Point *point) {
	printf("Coordinates -> x: %f, y: %f\n", point->x, point->y);
}

int main() {
    // Create an Arena
	Arena *arena = arena_init(1024);

    // Allocate on the arena, if the capacity is full it will automatically allocate new arena
	float *a = (float *)arena_alloc(arena, sizeof(float));
	float *b = (float *)arena_alloc(arena, sizeof(float));

	Point *p = (Point *)arena_alloc(arena, sizeof(Point));
	Point *p1 = (Point *)arena_alloc(arena, sizeof(Point));

	*a = 5.33f;
	*b = 6.34f;
	p->x = *a;
	p->y = *b;

	p1->x = *b;
	p1->y = *a;

	coordinates(p);
	coordinates(p1);

    // Free the arena, it will free all the allocations done on it
	arena_free(arena);
}
```
