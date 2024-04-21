#include <stdio.h>
#include "../mstring.h"
int main(){
    //                         ChCh Eng Ja  : Chinese; Hello; a
    MString str = mstr_strdup("中文Helloあ!");
    printf("Original string       : %s\n", str);
    mstr_insert(str, 30340, 2); // "的"
    printf("String after insertion: ");
    printf(str);
    printf("\nThe UTF32 of str with a offset of 3bytes: %u\n\n", mstr_one(str+3));
    /*
    print("All ... string:")
    for c in str:
        print(c, end=' ')
    */
   printf("All the UTF32 of this string:\n");
    MStringIter iter = str;
    for (MUnicode c; c = mstr_one(iter); mstr_next(&iter))
        printf("%u ", c);
    printf("\n\nThe Original data:\n");
    for (unsigned char *c=&str[0]; *c; c++)
        printf("%u ", *c);
    printf("\n");
    return 0;
}