#include "../include/binary-search-tree.h"
#include <iostream>

int main()
{
    BST<int> tree;
    for(int i = 1; i <= 10; ++i)
    {
        tree.insert(i);
    }
    tree.levelOrderTraversal();
 return 0;   
}
