#ifndef _RED_BLACK_TREE_H_
#define _RED_BLACK_TREE_H_

#include <iostream>
#include <utility>


template <typename T>
class RedBlackTree 
{
    public:
        struct Node {
            Node(const T& val,Node* p = nullptr,bool c = false, 
                    Node* l = nullptr,Node* r = nullptr) : data{val},
                parent{p}, left{l}, right{r}
            {}
            Node(T&& val,Node* p = nullptr,bool c = false, 
                    Node* l = nullptr,Node* r = nullptr) : data{std::move(val)},
                parent{p}, left{l}, right{r}
            {}

            T data;
            Node *parent;
            Node *left;
            Node *right;
            bool color;
        };
    private:
        void preOrderHelper(Node*) const;
        void inOrderHelper(Node*) const;
        void postOrderHelper(Node*) const;
        Node* searchTreeHelper(Node*,const T&) const;
        void deleteFix(Node*);
        void rbTransplant(Node*,Node*);
        void deleteNodeHelper(Node*,const T&);
        void insertFix(Node*);
        void copyHelper(Node*,const Node*,const RedBlackTree&);
        void clearHelper(Node*);
    public:
        RedBlackTree();
        RedBlackTree(const RedBlackTree&);
        RedBlackTree(RedBlackTree&&);
        ~RedBlackTree();
    public:
        RedBlackTree& operator=(const RedBlackTree&);
        RedBlackTree& operator=(RedBlackTree&&);
    public:
        bool empty() const
        {
            return root == NILL;
        }
        void clear()
        {
            if(!this->empty())
            {
                clearHelper(root);
                root = NILL;
            }
        }
        void preorder() const
        {
            preOrderHelper(this->root);
        }
        void inorder() const
        {
            inOrderHelper(this->root);
        }
        void postorder() const
        {
            postOrderHelper(this->root);
        }
        Node* searchTree(const T& k) const
        {
            return searchTreeHelper(this->root, k);
        }
        void leftRotate(Node*);
        void rightRotate(Node*);
        void insert(const T&);
        void insert(T&&);
        const T& getRoot() const 
        {
            return this->root->data;
        }
        void deleteNode(const T& data) 
        {
            deleteNodeHelper(this->root, data);
        }
    private:
        Node* root;
        Node* NILL;
};

#include "RedBlackTree.hpp"

#endif /* _RED_BLACK_TREE_H_ */
