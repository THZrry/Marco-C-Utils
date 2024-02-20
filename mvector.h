/*
Marco Vector
Using Vectors in C like in C++.
C standard: gnuc99 (isoc99+typeof)
In C:
    Marcos will help you write LIKE C++ vectors.
    WARNING: You can only use for data > 4 bytes per size!
             Because (vector-1) is an int saves the size!
    References will be pointers.
In C++:
    Your code will be translated to C++ vectors.

Usage:
    Vector(type) vector = New_Vector(type);      // define a vector
    except these, all functions are below alike:
        Vector_[original method name](vector, args...);
    Now support:
    Vector_size
    Vector_push_back
    Vector_insert    *: not completed, only two arguments (vector, index)
    Vector_erase
    Vector_popback
    Vector_clear
    Vector_at
    Vector_begin
    Vector_end
    Vector_front
    Vector_back
    Vector_release   *: extra function, C++ edition has it but no effect.

Example 1
############################################################
Vector(int) arr = New_vector(int);
for (int i=9; i>=0; i--)
    Vector_push_back(arr, i);
for (int i=0; i<Vector_size(arr); i++)
    printf("i: %d, data: %d\n", i, arr[i]);

######################### output ###########################
i: 0 data: 9
......
i: 9 data: 0

(
Vector_erase Marco function rewrite: https://zjyfdu.github.io/2019/02/14/C%E5%AE%8F%E5%87%BD%E6%95%B0%E9%87%8D%E8%BD%BD/
)

Lisence: WTFPL
Author : THZrry(github.com/THZrry)
*/

#ifndef _MVECTOR_
#define _MVECTOR_

# ifndef __cplusplus
/* C Define (main body) */
#include <malloc.h>
/* tool */
#define _Vector_GetMacro(_1,_2,NAME,...) NAME
/* marcos */
#define Vector(type)                             type*
#define New_vector(type)                         ((type*)calloc(1,sizeof(type))+1)
#define Vector_size(vector)                      (*(int*)(vector-1))
#define Vector_empty(vector)                     (Vector_size(vector)>0)
#define Vector_push_back(vector,x)               do{                                               \
        typeof(vector) new_vector = (typeof(vector))realloc(vector-1,(Vector_size(vector)+2)*(sizeof *vector));  \
        vector = new_vector+1;                                                                     \
        Vector_size(vector)++;                                                                     \
        vector[Vector_size(vector)-1] = x;                                                         \
        }while(0)
#define Vector_insert(vector,index,x)            do{                                               \
        vector = (typeof(vector))realloc(vector-1, Vector_size(vector)++*(sizeof *vector))+1;      \
        for (int i=Vector_size(vector); i>index; --i)                                              \
            vector[i] = vector[i-1];                                                               \
        vector[index] = x;                                                                         \
        }while(0)
#define Vector__erase1(vector,index)             do{                                               \
        for (int i=index+1; i<Vector_size(vector); i++)                                            \
            vector[i-1] = vector[i];                                                               \
        vector = (typeof(vector))realloc(vector-1, Vector_size(vector)--*(sizeof *vector))+1;      \
        }while(0)
#define Vector__erase2(vector,first,last)        do{                                               \
        int gap=last-first, i, j;                                                                  \
        for (i=last; i<Vector_size(vector); i++)                                                   \
            vector[i-gap] = vector[i];                                                             \
        Vector_size(vector) -= gap;                                                                \
        vector = (typeof(vector))realloc(vector-1, Vector_size(vector)*(sizeof *vector))+1;        \
        }while(0)
#define Vector_erase(vector,...)                _Vector_GetMacro(__VA_ARGS__, Vector__erase2, Vector__erase1, ...)(vector, __VA_ARGS__)
#define Vector_pop_back(vector)                  Vector_erase(vector, Vector_size(vector)-1)
#define Vector_clear(vector)                     do{                                               \
        vector = (typeof(vector))realloc(vector-1, sizeof *vector)+1;                              \
        Vector_size(vector) = 0;                                                                   \
        }while(0)
#define Vector_at(vector,pos)                    (vector+pos)
#define Vector_begin(vector)                     Vector_at(vector, 0)
#define Vector_end(vector)                       Vector_at(vector, Vector_size(vector)-1)
#define Vector_front(vector)                     Vector_at(vector, 0)
#define Vector_back(vector)                      Vector_at(vector, Vector_size(vector)-1)
#define Vector_release(vector)                   (free(vector-1))

#else
/* C++ Define (compatibling in C++) */

#include <vector>
#define Vector(type)                             std::vector<type>
#define New_vector(type)                         std::vector<type>()
#define Vector_size(vector)                      vector.size()
#define Vector_empty()                           vector.empty()
#define Vector_push_back(vector,x)               vector.push_back(x)
#define Vector_insert(vector,index,x)            vector.insert(index,x)
#define Vector_erase(vector,...)                 vector.erase(__VA_ARGS__)
#define Vector_pop_back(vector)                  vector.pop_back()
#define Vector_clear(vector)                     vector.clear()
#define Vector_at(vector,pos)                    vector.at(pos)
#define Vector_begin(vector)                     vector.begin()
#define Vector_end(vector)                       vector.end()
#define Vector_front(vector)                     vector.front()
#define Vector_back(vector)                      vector.back()
#define Vector_release(vector)                   do{}while(0)
#endif

#endif
