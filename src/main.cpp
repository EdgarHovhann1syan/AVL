#include "../include/avl_tree.h"
#include <iostream>

int main()
{
    AVL<int> tree;
    for(int i = 1; i < 10; ++i)
    {
        tree.insert(i);
    }
    tree.postOrderTraversal();
 return 0;   
}
