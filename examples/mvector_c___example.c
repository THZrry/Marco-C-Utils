/*
Marco Vector test for C.
Though marcos, you can use vector without extra type signing.
Metion:
    Don't write code like `Vector(int) vector_b = vector_a;` though pointer address may change!
    // Size is int, not size_t (Solved)
    No check for calloc/malloc failing.
*/
#include <stdio.h>
#include "../mvector.h"

int main(){
    Vector(int) arr = New_vector(int);
    for (int i=9; i>=0; i--)
        Vector_push_back(arr, i);
    Vector_erase(arr, 2, 5); 
    Vector_insert(arr, 3, 30);

    for (int i=0; i<Vector_size(arr); i++)
        printf("i: %d, data: %d\n", i, arr[i]);
    printf("\nThe fourth element: %d\n", *Vector_at(arr, 3));    // Metion this '*'!

    Vector_clear(arr);
    printf("Now the length of vector: %llu\n", Vector_size(arr));
    Vector_release(arr);
    printf("(C)  Now the vector has been released.\n");
     
    return 0;
}

