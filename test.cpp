#include <iostream>
#include <map>
#include <set>
#include "RedBlackTree.h"

template class RedBlackTree<int>;

int main()
{
    RedBlackTree<int> tree;
    tree.insert(10);
    tree.insert(18);
    tree.insert(7);
    tree.insert(15);
    tree.insert(16);
    tree.insert(30);
    tree.insert(25);
    tree.insert(40);
    tree.inorder();
    tree.deleteNode(25);
    tree.deleteNode(40);
    std::cout << std::endl;
    RedBlackTree<int> tree1 = std::move(tree);
    tree1.inorder();
    tree1.clear();
    std::cout << std::endl;
}
