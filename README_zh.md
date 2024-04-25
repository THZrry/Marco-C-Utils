# Mple Si
[English](README.md) **简体中文**
***
旧名称为`Macro C Utils`现已改名。这是一个简单的C语言头文件库，包含一些简单的功能。

# MVector
这是个简单的Vector，可以像C数组或者C++的vector一样调用。增长因子为50%，应该和msvc STL是一样的。
```C
#include "mvector.h"
void try_vector(){
    Vector(int) vect = New_Vector(int);
    // C++风格
    Vector_push_back(vect, 0);
    Vector_insert(vect, 0, 0x20);
    printf("第一个元素：%d\n", *Vector_at(vect, 0));
    // C风格
    printf("第二个元素：%d\n", vect[1]);
    // 记得释放！
    Vector_release(vect);
}
```

# MString
这是一个简单的UTF-8库，有着一些python风格接口。注意此部分**未完成**。
让我们先看看python处理字符串的一种方法：
```python
for char in string:
    do_something(char)
```
现在你也有机会这么做！像下面这样：
```C
MStringIter iter = string; // Mstring string;
for (MUnicode chr; chr=mstr_one(iter); mstr_next(&iter))
    do_something(chr);     // 第一个参数的类型：MUnicode
```
这只是一部分。去看看`mstring.h`的更多内容吧！


# RBTree
别用，还有BUG不会修呢。
