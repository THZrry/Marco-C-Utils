# Mple Si
**English** [简体中文](README_zh.md)
***
This is a SiMple C headers library. In the beginning its name was `Macro C Utils` and now renamed and not only based on macros.

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

# RBTree
Don't se this though it's not completed.