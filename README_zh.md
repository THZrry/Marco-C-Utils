# Marco C Utils
[English](README.md) **简体中文**
***
目前名称暂定此。起因是我写一个代码到处都是内存错误，心烦意乱，跑过来写点C的Vector。
但目前我见到的C的Vector都太重了，于是将这个仅包含宏的vector发出来，并准备往里面加些别的内容。
***

# MVector
这是个简单的Vector，可以像C数组或者C++的vector一样调用。增长因子为50%，应该和msvc STL是一样的。
```C
#include "mvector.h"
void try_vector(){
    Vector(int) vect = New_Vector(int);
    // C++风格
    Vector_push_back(vect, 0);
    Vector_insert(vect, 0, 0x20);
    printf("The first element: %d\n", *Vector_at(vect, 0));
    // C风格
    printf("The second element: %d\n", vect[1]);
    // 记得释放！
    Vector_release(vect);
}
```

# RBTree
有BUG，慎用。目前精力在mstring上，不维护这个破东西。
插入数据要，旋转树时会出Segmentation fault。
代码比较乱，目前改不了，求高手。
