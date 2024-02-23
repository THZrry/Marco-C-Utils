/*
Marco Vector test for C++.
Those marco functions are references to the orign vector methods.
*/
#include <stddef.h>
#include <iostream>
#include "../mvector.h"

int main(){
    Vector(int) arr = New_vector(int);
    for (int i=9; i>=0; i--)
        Vector_push_back(arr, i);
    Vector_erase(arr, 2, 5);
    //Vector_insert(arr, 3, 30);

    for (size_t i=0; i<Vector_size(arr); i++)
        std::cout<<"i: "<< i<<" data: "<< arr[i]<< '\n';
    std::cout<<"\nThe fourth element: "<< Vector_at(arr, 3)<< '\n';

    Vector_clear(arr);
    std::cout<<"Now the length of vector: "<< Vector_size(arr)<< '\n';
    Vector_release(arr);
    std::cout<<"(C++)Now the vector is still alive.\n";
    return 0;
}

