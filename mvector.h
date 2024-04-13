/*
Marco Vector
Using Vectors in C like in C++.
C standard: gnuc99 (isoc99+typeof)
In C:
    Marcos will help you write LIKE C++ vectors.
    References will be pointers.
In C++:
    Your code will be translated to C++ vectors.
    Or define _MFORCE_C_ to force C version.
    But iterator is not supported!

Usage:
    Vector(type) vector = New_Vector(type);      // define a vector
    except these, all functions are below alike:
        Vector_[original method name](vector, args...);
    Now support:
    Vector_size
    Vector_empty
    Vector_capacity
    Vector_reverse
    Vector_push_back
    Vector_insert    *: not completed, only two arguments (vector, index)
    Vector_erase
    Vector_pop_back
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
Vector__erase2 Daff's Device       : https://zhuanlan.zhihu.com/p/284223705
)

Lisence: WTFPL
Author : THZrry(github.com/THZrry)

Chengelog:
2024.4.13
  Now the "char" in 3.30 has changed to be size_t, and it supports reserving now.
  Now Vector__erase1 calls Vector__erase2 (instead of its own code)
  Added Vector_capacity, Vector_reserve, _vector_count_reverse
  Added _MFORCE_C_ marco, to force C in C++.
2024.3.30
  Now offset is absoultely, so the type is not restricted to int or bigger.
  Bugfix in earase functions.
  TODO: there's a more unsigned char's pos in vector, is for expanding use.
2024.2.23
  [C++] Changed iterator use to index use (look at cpptest)
  Changed size saving type to size_t
  Rewrited Vector__erase2 using Daff's Devices
  Add ranging check to Vector_at
2024.2.20
  First Release
*/

#ifndef _MVECTOR_
#define _MVECTOR_

/* tool */
#define _vector_get_macro(_1,_2,NAME,...) NAME

#if !defined(__cplusplus) || defined(_MFORCE_C_)
#  ifdef __cplusplus
extern "C"{
#  endif
/* C Define (main body) */
#include <malloc.h>
#include <stddef.h>

#ifndef _mmalloc             /* Customize memory pool */
#define _mmalloc  malloc
#define _mcalloc  calloc
#define _mrealloc realloc
#define _mfree    free
#endif
size_t _vector_count_reserve(size_t now){
    switch (now){
        case 0: return 2;
        case 1: return 4;
        case 2: return 6;
        case 3: return 8;
        default: return now + (now>>1);
    }
}
/* marcos */
#define _VOFFS                                   (sizeof(size_t) << 1)
#define Vector(type)                             type*
#define New_vector(type)                         ((type*)(_mcalloc(1,_VOFFS)+_VOFFS))
#define Vector_size(vector)                      (*(size_t*)((void*)(vector)-_VOFFS))
#define Vector_empty(vector)                     (Vector_size(vector)>0)
#define Vector_capacity(vector)                  (*(size_t*)((void*)(vector)-sizeof(size_t)))
#define Vector_reserve(vector,x)                 do{                                               \
        vector = _mrealloc((void*)vector-_VOFFS,(x*sizeof(*vector) + _VOFFS)) + _VOFFS;            \
        Vector_capacity(vector) = x;                                                               \
        }while(0)
#define Vector_push_back(vector,x)               do{                                               \
        if (Vector_capacity(vector) <= Vector_size(vector))                                        \
            Vector_reserve(vector, _vector_count_reserve(Vector_size(vector)));                    \
        vector[Vector_size(vector)++] = x;                                                         \
        }while(0)
#define Vector_insert(vector,index,x)            do{                                               \
        if (Vector_capacity(vector) <= Vector_size(vector))                                        \
            Vector_reserve(vector, _vector_count_reserve(Vector_size(vector)));                    \
        for (size_t i=Vector_size(vector); i>index; --i)                                           \
            vector[i] = vector[i-1];                                                               \
        vector[index] = x;                                                                         \
        Vector_size(vector)++;                                                                     \
        }while(0)
#define Vector__erase1(vector,index)             Vector__erase2(vector, index, index+1)
#define Vector__erase2(vector,first,last)        do{                                               \
        typeof(vector) to = vector + first,      from = vector + last;                             \
        register size_t count = Vector_size(vector) - last;                                        \
        register size_t n = count / 4;                                                             \
        switch (count % 4){                                                                        \
            case 0: do{ *to++ = *from++;                                                           \
            case 3:     *to++ = *from++;                                                           \
            case 2:     *to++ = *from++;                                                           \
            case 1:     *to++ = *from++;                                                           \
                    }while (n --> 0);                                                              \
        };                                                                                         \
        Vector_size(vector) -= last-first;                                                         \
        }while(0)
#define Vector_erase(vector,...)                _vector_get_macro(__VA_ARGS__, Vector__erase2, Vector__erase1, ...)(vector, __VA_ARGS__)
#define Vector_pop_back(vector)                  Vector_erase(vector, Vector_size(vector)-1)
#define Vector_clear(vector)                     do{Vector_size(vector) = 0;}while(0)
#define Vector_at(vector,pos)                    (vector + (pos>0? (pos<Vector_size(vector)? pos: Vector_size(vector)-1): 0))
#define Vector_begin(vector)                     (vector)
#define Vector_end(vector)                       (vector + Vector_size(vector) - 1)
#define Vector_front(vector)                     (vector)
#define Vector_back(vector)                      (vector + Vector_size(vector) - 1)
#define Vector_release(vector)                   (_mfree((void*)vector-_VOFFS))

#  ifdef _cplusplus
}
#  endif
#else
/* C++ Define (compatibling in C++) */
/* If defined _MFORCE_C_, this will not be avaliable. */
#include <vector>
#define Vector(type)                             std::vector<type>
#define New_vector(type)                         std::vector<type>()
#define Vector_size(vector)                      vector.size()
#define Vector_empty()                           vector.empty()
#define Vector_capacity()                        vector.capacity()
#define Vector_reserve(x)                        vector.capacity(x)
#define Vector_push_back(vector,x)               vector.push_back(x)
#define Vector_insert(vector,index,x)            vector.insert(index,x)
#define Vector__erase1(vector,index)             vector.erase(vector.begin()+index)
#define Vector__erase2(vector,first,last)        vector.erase(vector.begin()+first, vector.begin()+last)
#define Vector_erase(vector,...)                _Vector_GetMacro(__VA_ARGS__, Vector__erase2, Vector__erase1, ...)(vector, __VA_ARGS__)
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
