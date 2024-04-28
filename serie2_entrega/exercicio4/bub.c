#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

extern void bubble_sort(void *base, size_t nelements, size_t width, int (*compare)(const void *, const void *));

int compare_ints(const void *a, const void *b);
double time1, timedif; 


int main() {
    // Seed for random number generation
    srand(time(NULL));


    time1 = (double) clock();            /* get initial time */
    time1 = time1 / CLOCKS_PER_SEC;      /*    in seconds    */
    // Array size
    size_t array_size = 10000;

    // Allocate memory for the array
    int *random_numbers = malloc(sizeof(int) * array_size);

    // Initialize the array with random numbers
    for (size_t i = 0; i < array_size; i++) {
        random_numbers[i] = rand();
    }



    // Sort the array using bubble_sort
    bubble_sort(random_numbers, array_size, sizeof(int), compare_ints);



    // Free allocated memory
    free(random_numbers);
    
    timedif = ( ((double) clock()) / CLOCKS_PER_SEC) - time1;
    printf("The elapsed time is %lf seconds\n", timedif);

    return 0;
}