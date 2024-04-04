#error "This contains BUGS!!Exiting..."
#include <stdio.h>

#ifndef _mmap_malloc
#include <malloc.h>
#define _mmap_malloc  malloc
#define _mmap_calloc  calloc
#define _mmap_realloc realloc
#define _mmap_free    free
#endif

typedef enum{
    MRED, MBLACK
}_mcolor;

#define _mcomp_type(type,v1,v2) ({ (type v1) ==(type v2) ?0:( (type v1)<(type v2)?1:2 );})
#define _mcomp(v1,v2)  ({\
    register int res = 0;\
    switch(sizeof(v1)){\
        case 1:\
            res = _mcomp_type((unsigned char), v1, v2);break;\
        case 2:\
            res = _mcomp_type((unsigned short), v1, v2);break;\
        case 4:\
            res = _mcomp_type((unsigned int), v1, v2);break;\
        default:\
            for (unsigned char *l=((void*)v1), *r=((void*)v2); res==0 || l<(((void*)v1)+sizeof(v1)); l++, r++)\
                res = _mcomp_type((unsigned char), (*l), (*r));\
    }\
    res;\
})

#define Map(ktype,vtype) struct _MapNode_##ktype##_##vtype{\
    int key;\
    int value;\
    struct _MapNode_##ktype##_##vtype *parent;\
    struct _MapNode_##ktype##_##vtype *left;\
    struct _MapNode_##ktype##_##vtype *right;\
    _mcolor color;\
}*

#define create_node(p,k,v) ({\
    typeof(p) node = _mmap_malloc(sizeof(*p));\
    node->key  = k;\
    node->value  = v;\
    node->parent = p;\
    node->left   = NULL;\
    node->right  = NULL;\
    node->color  = MRED;\
    node;\
})

#define rotate_left(root,x) do{\
    typeof(root) y = x->right;\
    x->right = y->left;\
    if (y->left != NULL){\
        y->left->parent = x;\
    }\
    y->parent = x->parent;\
    if (x->parent == NULL)\
        root = y;\
    else if (x->parent->left == x)\
        x->parent->left = y;\
    else\
        x->parent->right = y;\
    y->left   = x;\
    x->parent = y;\
}while(0)

#define rotate_right(root,y) do{\
    typeof(root) x = y->left;\
    y->left = x->right;\
    if (x->right != NULL)\
        x->right->parent = y;\
    x->parent = y->parent;\
    if (y->parent == NULL)\
        root = x;\
    else if (y == y->parent->left)\
        y->parent->left = x;\
    else\
        y->parent->right = x;\
    x->right  = y;\
    y->parent = x;\
}while(0)

//#define rotate_left(root,z)  root
//#define rotate_right(root,z) root

#define _insert_fixing(root,z) do{\
    typeof(root) y;\
    if (z->parent == NULL || z->parent->parent == NULL)\
        break;\
    while (z->parent != NULL && z->parent->color == MRED){\
        if (z->parent == z->parent->parent->left){\
            y = z->parent->parent->right;\
            z->parent->parent->color = MRED;\
            z = z->parent->parent;\
            if (y != NULL && y->color == MRED){\
                z->parent->color = MBLACK;\
                y->color = MBLACK;\
            }else{\
                if (z == z->parent->right){\
                    z = z->parent;\
                    rotate_left(root, z);\
                }\
                rotate_right(root, z->parent->parent);\
            }\
        }else{\
            y = z->parent->parent->left;\
            if (y != NULL && y->color == MRED) {\
                z->parent->color = MBLACK;\
                y->color = MBLACK;\
                z->parent->parent->color = MRED;\
                z = z->parent->parent;\
            }else{\
                if (z == z->parent->left) {\
                    z = z->parent;\
                    rotate_right(root, z);\
                }\
                z->parent->color = MBLACK;\
                z->parent->parent->color = MRED;\
                rotate_left(root, z->parent->parent);\
            }\
        }\
    }\
    root->color = MBLACK;\
}while(0)

#define insert_node(root,k,v) do{\
    typeof(root) z = create_node(root, k, v);\
    typeof(root) y  = NULL;\
    typeof(root) x = root;\
    while (x != NULL){\
        y = x;\
        if (z->key < x->key)\
            x = x->left;\
        else\
            x = x->right;\
    }\
    z->parent = y;\
    if (y == NULL)\
        root = z;\
    else if (z->key < y->key)\
        y->left  = z;\
    else if(z->key > y->key)\
        y->right = z;\
    else{\
        y->value = v;\
        _mmap_free(z);\
        break;\
    }\
    _insert_fixing(root, z);\
}while(0)

#define _delete_fixing(root,node) ({\
    typeof(root) sibling = NULL;\
    while  (node != root && node->color == MBLACK){\
        if (node == node->parent->left){\
            sibling = node->parent->right;\
            if (sibling->color == MRED){\
                sibling->color = MBLACK;\
                node->parent->color = MRED;\
                rotate_left(root, node->parent);\
                sibling = node->parent->right;\
            }\
            if (sibling->left->color == MBLACK && sibling->right->color == MBLACK){\
                sibling->color = MRED;\
                node = node->parent;\
            }else{\
                if (sibling->right->color == MBLACK){\
                    sibling->left->color = MBLACK;\
                    sibling->color = MRED;\
                    rotate_right(root, sibling);\
                    sibling = node->parent->right;\
                }\
                sibling->color = node->parent->color;\
                node  ->parent->color = MBLACK;\
                sibling->right->color = MBLACK;\
                rotate_left(root, node->parent);\
                node = root;\
            }\
        }else{\
            sibling = node->parent->left;\
            if (sibling->color == MRED){\
                sibling->color = MBLACK;\
                node->parent->color = MRED;\
                rotate_left(root, node->parent);\
                sibling = node->parent->left;\
            }\
            if (sibling->right->color == MBLACK && sibling->left->color == MBLACK){\
                sibling->color = MRED;\
                node = node->parent;\
            }else{\
                if (sibling->left->color == MBLACK){\
                    sibling->right->color = MBLACK;\
                    sibling->color = MRED;\
                    rotate_left(root, sibling);\
                    sibling = node->parent->left;\
                }\
                sibling->color = node->parent->color;\
                node->parent->color = MBLACK;\
                sibling->left->color = MBLACK;\
                rotate_right(root, node->parent);\
                node = root;\
            }\
        }\
    }\
    node->color = MBLACK;\
    root;\
})

#define delete_node(root,k) do{\
    typeof(root) current  = root;\
    typeof(root) parent   = NULL;\
    typeof(root) deleting = NULL;\
    typeof(root) child    = NULL;\
    while (current != NULL){\
        if (current->key == k)\
            deleting = current;\
        if (current->key > k)\
            current = current->left;\
        else\
            current = current->right;\
    }\
    if (deleting == NULL)\
        break;\
    if (deleting->left == NULL || deleting->right == NULL)\
        parent = deleting;\
    else{\
        parent = deleting->right;\
        while (parent->left != NULL)\
            parent = parent->left;\
    }\
    if (parent->left != NULL)\
        child = parent->left;\
    else\
        child = parent->right;\
    if (child != NULL)\
        child->parent = parent->parent;\
    if (parent->parent == NULL)\
        root = child;\
    else if (parent == parent->parent->left)\
        parent->parent->left  = child;\
    else\
        parent->parent->right = child;\
    if (parent != deleting){\
        deleting->key   = parent->key;\
        deleting->value = parent->value;\
    }\
    if (parent->color == MBLACK)\
        root = _delete_fixing(root, child);\
    _mmap_free(parent);\
}while(0)

#define search_node(root,k) ({\
    typeof(root) x = root;\
    while  (x != NULL && x->key != k){\
        if (x->key < k)\
            x = x->right;\
        else\
            x = x->left;\
    }\
    x;\
})
/*
#define release_tree(root) do{\
    if (root->left)\
        release_tree(root->left);\
    if (root->right)\
        release_tree(root->right);\
    _mmap_free(root);\
}while(0)
*/
/*
int main(){
    //Node root;
    //Node *root = create_node(0, 0);
    Node *root = NULL;
    insert_node(&root, 10, 1);
    insert_node(&root, 20, 2);
    insert_node(&root, 30, 3);
    insert_node(&root, 40, 4);
    insert_node(&root, 40, 4);
    insert_node(&root, 50, 5);
    insert_node(&root, 60, 6);
    insert_node(&root, 70, 7);
    insert_node(&root, 80, 8);
    insert_node(&root, 90, 9);
    insert_node(&root, 100, 10);
    delete_node(&root, 90);
    printf("Tree:\n");
    print_all(root);
    printf("\n%d ", search_node(&root, 70)->value);
    printf("%d\n", (int)search_node(&root, 90));
    release_tree(root);
    return 0;
}
*/

int main(){
    //Node root;
    //Node *root = create_node(0, 0);
    Map(int, int) root = NULL;
    insert_node(root, 10, 1);
    insert_node(root, 20, 2);
    insert_node(root, 30, 3);
    /*insert_node(&root, 40, 4);
    insert_node(&root, 40, 4);
    insert_node(&root, 50, 5);
    insert_node(&root, 60, 6);
    insert_node(&root, 70, 7);
    insert_node(&root, 80, 8);
    insert_node(&root, 90, 9);
    insert_node(&root, 100, 10);*/
    delete_node(root, 20);
    //printf("Tree:\n");
    printf("\n%d ", search_node(root, 10)->value);
    //printf("%d\n", (int)search_node(&root, 90));
    //release_tree(root);
    return 0;
}
