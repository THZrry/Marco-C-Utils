/*
mstring.h Marco String in UTF-8
now it's in early coding stage and it can only process
 Unicode less than or equal to 4 bytes in size through
 a hard-limit in code.

A simple tour is here:
    Let's see how python process strings in one way:
    ```python3
    for char in string:
        do_something(char)
    ```
    Now you have the same chance to do it! Like this:
    ```C99
    MStringIter iter = string; // Mstring string;
    for (MUnicode chr; chr=mstr_one(iter); mstr_next(&iter))
        do_something(chr);     // type of arg0: MUnicode
    ```
    Although the code is longer, this is a possible solution.
    The iter points to a (unsigned)char which is the head of a
UTF-8 character. Based on this, `mstr_getat` returns the
MUnicode on index, which is based on character-based count ways
instead of byte-based.
    The benifits of this library is simple: do any thing in
cimple ways. Maybe it's not the simplest one, it's enough. So I
want to port some python-like apis here, after the base frame's
done.

Usage:
    types:
        typedef Vector(unsigned char) MString;  A vector storages unsigned chars.
        typedef unsigned char* MStringIter;     MStringIter, usage below.
        typedef uint32_t MUnicode;              MUnicode is unsigned int32 to ensure it can storage any unicode.
    functions:
        mstr_*(functions in string.h)           will support them with UTF-8
        mstr_strlen(const MString)              the length of MString, based on characters.
        mstr_size(const MString)                equal to cstring::strlen, but in O(1) because of Vector
        mstr_one(const unsinged char *s)        return the Unicode UTF32 of s
        mstr_next(MStringIter s)                point s to next Unicode's head

*/

#ifndef _HMSTRING_
#define _HMSTRING_
#ifdef __cplusplus
extern "C"{
#endif
#include <stdint.h>
#include "mvector.h"
#define New_string() New_vector(char)

typedef Vector(unsigned char) MString;
typedef unsigned char* MStringIter;
typedef uint32_t MUnicode;

MString mstr_strdup(const char *s){
    MString nstr = New_string();
    for (const char *ptr=s; *ptr; ptr++)
        Vector_push_back(nstr, *ptr);
    Vector_push_back(nstr, '\0');
    return nstr;
}

size_t mstr_strlen(const MString s){
    /* Return the length of string in character-based count ways. */
    size_t length = 0;
    for (const unsigned char *chr=s; *chr; chr++, length++)
        if (*chr > 0b11110000)
            chr += 3;
        else if (*chr > 0b11100000)
            chr += 2;
        else if (*chr > 0b11000000)
            chr++;
    return length;
}

size_t mstr_strsize(const MString s){
    /* This function returns the size of a string without \0. */
    return Vector_size(s) - 1;
}

MUnicode mstr_one(const MStringIter s){
    MUnicode chr = 0;
    if (*s >= 0b11110000){
        chr += (s[0] - 0b11110000) << 18;
        chr += (s[1] - 0b10000000) << 12;
        chr += (s[2] - 0b10000000) << 6;
        chr += (s[3] - 0b10000000);
    }else if (*s >= 0b11100000){
        chr += (s[0] - 0b11100000) << 12;
        chr += (s[1] - 0b10000000) << 6;
        chr += (s[2] - 0b10000000);
    }else if (*s >= 0b11000000){
        chr += (s[0] - 0b11000000) << 6;
        chr += (s[1] - 0b10000000);
    }else
        chr = *s;
    return chr;
}

void mstr_next(MStringIter *s){
    if (**s >= 0b11110000)
        *s += 4;
    else if (**s >= 0b11100000)
        *s += 3;
    else if (**s >= 0b11000000)
        *s += 2;
    else
        *s += 1;
}

void mstr_insert(MString s, const MUnicode chr, size_t index){
    size_t i;
    MStringIter iter = s;
    for (MUnicode c=mstr_one(iter), i=0; (i < index)&&(c=mstr_one(iter)); mstr_next(&iter), i++);
    index = (size_t)(iter - s);
    if (chr > 65536){
        Vector_insert(s, index, chr & 0x000f);
        Vector_insert(s, index, (chr & 0x00f0) + 0x80);
        Vector_insert(s, index, (chr & 0x0f00) + 0x80);
        Vector_insert(s, index, (chr & 0xf000) + 0xf0);
    }else if (chr > 2048){
        Vector_insert(s, index, (chr & 0x3f) + 0x80);
        Vector_insert(s, index, ( (chr & 0xfc0) >> 6 ) + 0x80);
        Vector_insert(s, index, ( (chr & 0xf000)>>12 ) + 0xe0);
    }else if (chr > 128){
        Vector_insert(s, index, chr & 0x0f);
        Vector_insert(s, index, (chr & 0xf0) + 0xc0);
    }else{
        Vector_insert(s, index, chr);
    }
}

MUnicode mstr_getat(MString s, size_t n){
    MStringIter iter = s;
    size_t index  = 0;       // Unicode index
    for (MUnicode c=mstr_one(iter);(index<n) && (c=mstr_one(iter)); mstr_next(&iter), index++);
    return mstr_one(iter);
}

MStringIter mstr_strcat(MString dest, const MString src){
    Vector_erase(dest, Vector_size(dest)-1);
    MStringIter iter = src;
    for (MUnicode c=mstr_one(iter); c=mstr_one(iter); mstr_next(&iter))
        ;
}
#ifdef __cplusplus
// extern "C"{
}
#endif
#endif