#include <stdio.h>
#include <stdlib.h>  // For malloc() and free()

#define LENGTH 5
// Function to demonstrate static array
void static_array_example() {
    // Static array: size is known at compile time
    int static_array[LENGTH] = {1, 2, 3, 4, 5};  // Array with 5 elements

    // Accessing and printing elements of the static array
    printf("Static array elements:\n");
    for (int i = 0; i < 5; i++) {
        printf("static_array[%d] = %d\n", i, static_array[i]);
    }
}

// Function to demonstrate dynamic array
void dynamic_array_example() {
    int n;
    printf("Enter the size of the dynamic array: ");
    scanf("%d", &n);
    // Dynamic array: size is determined at runtime
    // Allocate memory dynamically using malloc()
    int *dynamic_array = (int *)malloc(n * sizeof(int));

    if (dynamic_array == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }

    // Initializing dynamic array elements
    for (int i = 0; i < n; i++) {
        dynamic_array[i] = i + 1;  // Assign values 1, 2, 3, ..., n
    }




    // Accessing and printing elements of the dynamic array
    printf("Dynamic array elements:\n");
    for (int i = 0; i < n; i++) {
        printf("dynamic_array[%d] = %d\n", i, dynamic_array[i]);
    }

    int new_size = n+10;
    dynamic_array = (int *)realloc(dynamic_array, new_size * sizeof(int));
    if (dynamic_array == NULL) {
        printf("Memory reallocation failed!\n");
        return;
    }
    for (int i = n; i < new_size; i++) {
        dynamic_array[i] = i + 1;  // Assign values 1, 2, 3, ..., n
    }

    // Accessing and printing elements of the dynamic array
    printf("Dynamic array elements:\n");
    for (int i = 0; i < new_size; i++) {
        printf("dynamic_array[%d] = %d\n", i, dynamic_array[i]);
    }

    // Free the dynamically allocated memory
    free(dynamic_array);
}

int main() {
    // Demonstrating static array
    static_array_example();

    // Demonstrating dynamic array
    dynamic_array_example();

    return 0;
}
