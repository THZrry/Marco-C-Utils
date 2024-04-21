# Marco C Utils
**English** [简体中文](README_zh.md)
***
This is the current name.
I wanna use a light c vector, but my known existing libraries are too heavy for me, so I put this cvector with only marcos here. I may add morethings in the future.

# MVector
this is a simple vector can be used like C arrays or C++ vectors. The increasing factor is 50%, that seems to be the same as msvc STL.
```C
#include "mvector.h"
void try_vector(){
    Vector(int) vect = New_Vector(int);
    // C++ like
    Vector_push_back(vect, 0);
    Vector_insert(vect, 0, 0x20);
    printf("The first element: %d\n", *Vector_at(vect, 0));
    // C like
    printf("The second element: %d\n", vect[1]);
    // Release!!
    Vector_release(vect);
}
```

# MString
a simple UTF-8 library with some python-like interfaces. NOT COMPLETED.
Let's see how python process strings in one way:
```python
for char in string:
    do_something(char)
```
Now you have the same chance to do it! Like this:
```C
MStringIter iter = string; // Mstring string;
for (MUnicode chr; chr=mstr_one(iter); mstr_next(&iter))
    do_something(chr);     // type of arg0: MUnicode
```
This is only a part. Explore `mstring.h` for more!

# About RBTree
Not For Now. Coding on mstring.
when it comes to inserting data with rotating, it crashes, with segmentation fault.
The code with a number of marcos is near unreadable, and I'm not able to solve.
