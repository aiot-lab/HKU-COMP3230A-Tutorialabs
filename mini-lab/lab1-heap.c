// file: lab1-heap.c
#include <stdio.h>
#include <stdlib.h>

int* initialize_array(int n){
    int *heap_arr = NULL;
    // TODO: 1. Allocate memory for 'n' integers using malloc. Assign the address to 'heap_arr'. (~1 line)
    
    if (heap_arr == NULL) {
        printf("Memory allocation failed!\n");
        return NULL;  // Exit with an error code
    }

    // TODO: 2. Use a loop to navigate through the array.
    // For each index 'i', set arr[i] to i * i (square of index). (~3 lines)
        
    return heap_arr;
}

int main(int argc, char *argv[]) {
    int *arr;  // Pointer for our dynamically allocated array

    // Check if the command line argument is provided
    if (argc != 2) {
        printf("Usage: %s <number_of_elements>\n", argv[0]);
        return 1;  // Exit with an error code
    }

    // Convert the command line argument to an integer
    int n = atoi(argv[1]);

    arr = initialize_array(n);

    for(int i=0; i<n; i++){
        printf("%d\t", arr[i]);
    }

    // TODO: 3. Free the dynamically allocated memory. (~1 line)
    
    return 0;
}