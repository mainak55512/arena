# Arena Allocator Library

A lightweight arena-style memory allocator for C projects.

## Features
- Simple initialization with a fixed capacity
- Automatically allocates memory if capacity is full
- Fast linear allocations using a pre-allocated buffer
- One-shot memory release via `arena_free()`
- C89 compatible

## Building & Installing

### Requirements
- CMake (>= 3.10 recommended)
- Clang or GCC

### Build Steps
1. Clone the repository in your project root.
    ```sh
    git clone https://github.com/mainak55512/arena.git
    ```
2. In your `CMakeLists.txt` add the following lines:
    ```cmake
    target_include_directories(${PROJECT_NAME} PRIVATE arena/include)
    add_library(arena STATIC arena/lib/arena.c)
    target_link_libraries(${PROJECT_NAME} PRIVATE arena)
    ```
3. ```sh
    mkdir build
    cd build
    cmake ..
    make
    ./your-executable
    ```

## Sample CMakeLists.txt

```cmake
    cmake_minimum_required(VERSION 3.10)
    project(arena_test)

    add_executable(${PROJECT_NAME} main.c)

    target_include_directories(${PROJECT_NAME} PRIVATE arena/include)
    add_library(arena STATIC arena/lib/arena.c)
    target_link_libraries(${PROJECT_NAME} PRIVATE arena)
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
	Arena *arena = arena_init(100);

	// Allocate on the arena, if the capacity is full it will automatically allocate new arena
	// Allocating for 10 integers
	int *arr = (int *)arena_alloc(arena, 10 * sizeof(int));
	for (int i = 0; i < 10; i++) {
		arr[i] = (i * 2) + 10;
	}
	printf("Int Arr: ");
	for (int i = 0; i < 10; i++) {
		printf("%d, ", arr[i]);
	}
	printf("\n");

	// Allocating for 10 floats
	float *arr1 = (float *)arena_alloc(arena, 10 * sizeof(float));
	for (int i = 0; i < 10; i++) {
		arr1[i] = (i * 2.5f) + 10;
	}
	printf("Float Arr: ");
	for (int i = 0; i < 10; i++) {
		printf("%f, ", arr1[i]);
	}
	printf("\n");

	// Allocating for Point struct
	Point *p = (Point *)arena_alloc(arena, sizeof(Point));
	p->x = 2.34f;
	p->y = 5.46f;

	coordinates(p);

	// Free the arena, it will free all the allocations done on it i.e. arr, arr1 & p
	arena_free(&arena);
}
```
