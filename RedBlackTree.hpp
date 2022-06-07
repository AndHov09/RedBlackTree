#ifndef _RED_BLACK_TREE_HPP_
#define _RED_BLACK_TREE_HPP_

template <typename T>
RedBlackTree<T>::RedBlackTree() : root{}, NILL{}
{
    NILL = new Node(T{},nullptr,0);
    root = NILL;
}

template <typename T>
RedBlackTree<T>::RedBlackTree(const RedBlackTree<T>& oth) : root{}, NILL{}
{
    NILL = new Node(T{});
    root = NILL;
    if(!oth.empty())
    {
        root = new Node(oth.root->data);
        copyHelper(root,oth.root,oth);    
    }
}

template <typename T>
RedBlackTree<T>::RedBlackTree(RedBlackTree<T>&& oth) : root{oth.root},NILL{oth.NILL}
{
    oth.root = oth.NILL = nullptr;
}

template <typename T>
RedBlackTree<T>::~RedBlackTree()
{
    if(!this->empty())
    {
        clearHelper(root);
        delete NILL;
        root = NILL = nullptr;
    }
}

template <typename T>
RedBlackTree<T>& RedBlackTree<T>::operator=(const RedBlackTree<T>& oth)
{
    if(this != &oth)
    {
        this->clear();
        root = new Node(oth.root->data);
        copyHelper(root,oth.root,oth);
    }
    return *this;
}

template <typename T>
RedBlackTree<T>& RedBlackTree<T>::operator=(RedBlackTree<T>&& oth)
{
    if(this != &oth)
    {
        this->clear();
        root = oth.root;
        NILL = oth.NILL;
        oth.root = oth.NILL = nullptr;
    }
    return *this;
}

template <typename T>
void RedBlackTree<T>::preOrderHelper(typename RedBlackTree<T>::Node* node) const
{
    if (node != NILL) 
    {
        std::cout << node->data << " ";
        preOrderHelper(node->left);
        preOrderHelper(node->right);
    }
}

template <typename T>
void RedBlackTree<T>::inOrderHelper(typename RedBlackTree<T>::Node* node) const
{
    if (node != NILL) 
    {
        inOrderHelper(node->left);
        std::cout << node->data << " ";
        inOrderHelper(node->right);
    }
}

template <typename T>
void RedBlackTree<T>::postOrderHelper(typename RedBlackTree<T>::Node* node) const
{
    if (node != NILL) 
    {
        postOrderHelper(node->left);
        postOrderHelper(node->right);
        std::cout << node->data << " ";
    }
}

template <typename T>
typename RedBlackTree<T>::Node* RedBlackTree<T>::searchTreeHelper(typename RedBlackTree<T>::Node* node,const T& key) const 
{
    if (node == NILL || key == node->data) 
    {
        return node;
    }

    if (key < node->data) 
    {
        return searchTreeHelper(node->left, key);
    }
    return searchTreeHelper(node->right, key);
}

template <typename T>
void RedBlackTree<T>::deleteFix(typename RedBlackTree<T>::Node* node)
{
    typename RedBlackTree::Node* uncle;
    while (node != root && node->color == 0) 
    {
        if (node == node->parent->left) 
        {
            uncle = node->parent->right;
            if (uncle->color == 1) 
            {
                uncle->color = 0;
                node->parent->color = 1;
                leftRotate(node->parent);
                uncle = node->parent->right;
            }
            if (uncle->left->color == 0 && uncle->right->color == 0) 
            {
                uncle->color = 1;
                node = node->parent;
            } else {
                if (uncle->right->color == 0) 
                {
                    uncle->left->color = 0;
                    uncle->color = 1;
                    rightRotate(uncle);
                    uncle = node->parent->right;
                }
                uncle->color = node->parent->color;
                node->parent->color = 0;
                node->right->color = 0;
                leftRotate(node->parent);
                node = root;
            }
        } else {
            uncle = node->parent->left;
            if (uncle->color == 1) 
            {
                uncle->color = 0;
                node->parent->color = 1;
                rightRotate(node->parent);
                uncle = node->parent->left;
            }
            if (uncle->right->color == 0 && uncle->right->color == 0)
            {
                uncle->color = 1;
                node = node->parent;
            } else {
                if (uncle->left->color == 0) 
                {
                    uncle->right->color = 0;
                    uncle->color = 1;
                    leftRotate(uncle);
                    uncle = node->parent->left;
                }
                uncle->color = node->parent->color;
                node->parent->color = 0;
                uncle->left->color = 0;
                rightRotate(node->parent);
                node = root;
            }
        }
    }
    node->color = 0;
}

template <typename T>
void RedBlackTree<T>::rbTransplant(typename RedBlackTree<T>::Node* ptr1,typename RedBlackTree<T>::Node* ptr2)
{
    if (ptr1->parent == nullptr) 
    {
        root = ptr2;
    } else if (ptr1 == ptr1->parent->left) 
    {
        ptr1->parent->left = ptr2;
    } else {
        ptr1->parent->right = ptr2;
    }
    ptr2->parent = ptr1->parent;
}

template <typename T>
void RedBlackTree<T>::deleteNodeHelper(typename RedBlackTree<T>::Node* node,const T& key) 
{
    typename RedBlackTree<T>::Node* ptr1 = NILL;
    typename RedBlackTree<T>::Node* ptr2;
    typename RedBlackTree<T>::Node* ptr3;
    while (node != NILL) 
    {
        if (node->data == key) 
        {
            ptr1 = node;
        }
        if (node->data <= key) 
        {
            node = node->right;
        } else {
            node = node->left;
        }
    }
    if (ptr1 == NILL) 
    {
        return;
    }
    ptr3 = ptr1;
    bool original_color = ptr3->color;
    if (ptr1->left == NILL) {
        ptr2 = ptr1->right;
        rbTransplant(ptr1, ptr1->right);
    } else if (ptr1->right == NILL) 
    {
        ptr2 = ptr1->left;
        rbTransplant(ptr1, ptr1->left);
    } else {
        ptr3 = ptr1->right->left != NILL ? ptr1->right->left : ptr1->right;
        original_color = ptr3->color;
        ptr2 = ptr3->right;
        if (ptr3->parent == ptr1)
        {
            ptr2->parent = ptr3;
        } else {
            rbTransplant(ptr2, ptr2->right);
            ptr3->right = ptr1->right;
            ptr3->right->parent = ptr3;
        }

        rbTransplant(ptr1, ptr3);
        ptr3->left = ptr1->left;
        ptr3->left->parent = ptr3;
        ptr3->color = ptr1->color;
    }
    delete ptr1;
    if (original_color == 0) {
        deleteFix(ptr2);
    }
}

template <typename T>
void RedBlackTree<T>::insertFix(typename RedBlackTree<T>::Node* node) {
    typename RedBlackTree<T>::Node* uncle;
    while (node->parent->color == 1) 
    {
        if (node == root) {
            break;
        }
        if (node->parent == node->parent->parent->right) 
        {
            uncle = node->parent->parent->left;
            if (uncle->color == 1) 
            {
                uncle->color = 0;
                node->parent->color = 0;
                node->parent->parent->color = 1;
                node = node->parent->parent;
            } else {
                if (node == node->parent->left) 
                {
                    node = node->parent;
                    rightRotate(node);
                }
                node->parent->color = 0;
                node->parent->parent->color = 1;
                leftRotate(node->parent->parent);
            }
        } else {
            uncle = node->parent->parent->right;

            if (uncle->color == 1) 
            {
                uncle->color = 0;
                node->parent->color = 0;
                node->parent->parent->color = 1;
                node = node->parent->parent;
            } else {
                if (node == node->parent->right) 
                {
                    node = node->parent;
                    leftRotate(node);
                }
                node->parent->color = 0;
                node->parent->parent->color = 1;
                rightRotate(node->parent->parent);
            }
        }
    }
    root->color = 0;
}

template <typename T>
void RedBlackTree<T>::insert(const T& key) 
{
    typename RedBlackTree<T>::Node* node = new Node(key,nullptr,1,NILL,NILL);
    typename RedBlackTree<T>::Node* y = nullptr;
    typename RedBlackTree<T>::Node* x = this->root;

    while (x != NILL) 
    {
        y = x;
        if (node->data < x->data) 
        {
            x = x->left;
        } else {
            x = x->right;
        }
    }
    node->parent = y;
    if (y == nullptr) 
    {
        root = node;
    } else { 
        if (node->data < y->data) 
        {
            y->left = node;
        } else {
            y->right = node;
        }
    }
    if (node->parent == nullptr) 
    {
        node->color = 0;
        return;
    }
    if (node->parent->parent == nullptr) 
    {
        return;
    }
    insertFix(node);
}

template <typename T>
void RedBlackTree<T>::insert(T&& key) 
{
    typename RedBlackTree<T>::Node* node = new Node(std::move(key),nullptr,1,NILL,NILL);
    typename RedBlackTree<T>::Node* y = nullptr;
    typename RedBlackTree<T>::Node* x = this->root;

    while (x != NILL)
    {
        y = x;
        if (node->data < x->data) 
        {
            x = x->left;
        } else {
            x = x->right;
        }
    }
    node->parent = y;
    if (y == nullptr) 
    {
        root = node;
    } else { 
        if (node->data < y->data) 
        {
            y->left = node;
        } else {
            y->right = node;
        }
    }
    if (node->parent == nullptr) 
    {
        node->color = 0;
        return;
    }
    if (node->parent->parent == nullptr) 
    {
        return;
    }
    insertFix(node);
}

template <typename T>
void RedBlackTree<T>::leftRotate(typename RedBlackTree<T>::Node* node) 
{
    typename RedBlackTree<T>::Node* tmp = node->right;
    node->right = tmp->left;
    if (tmp->left != NILL) 
    {
        tmp->left->parent = node;
    }
    tmp->parent = node->parent;
    if (node->parent == nullptr) 
    {
        this->root = tmp;
    } else 
    {
        if (node == node->parent->left)
        {
            node->parent->left = tmp;
        } else {
            node->parent->right = tmp;
        }
    }
    tmp->left = node;
    node->parent = tmp;
}

template <typename T>
void RedBlackTree<T>::rightRotate(typename RedBlackTree<T>::Node* node) 
{
    typename RedBlackTree<T>::Node* tmp = node->left;
    node->left = tmp->right;
    if (tmp->right != NILL) 
    {
        tmp->right->parent = node;
    }
    tmp->parent = node->parent;
    if (node->parent == nullptr) 
    {
        this->root = tmp;
    } else 
    {
        if (node == node->parent->right)
        {
            node->parent->right = tmp;
        } else {
            node->parent->left = tmp;
        }
    }
    tmp->right = node;
    node->parent = tmp;
}

template <typename T>
void RedBlackTree<T>::copyHelper(typename RedBlackTree<T>::Node* ptr1,
                            const typename RedBlackTree<T>::Node* ptr2,
                            const RedBlackTree<T>& oth)
{
    if(ptr2->left != oth.NILL)
    {
        ptr1->left  = new Node(ptr2->left->data,ptr1,ptr2->left->color,NILL,NILL);
        copyHelper(ptr1->left,ptr2->left,oth);
    }
    if(ptr2->right != oth.NILL)
    {
        ptr1->right = new Node(ptr2->right->data,ptr1,ptr2->left->color,NILL,NILL);
        copyHelper(ptr1->right,ptr2->right,oth);
    }
}

template <typename T>
void RedBlackTree<T>::clearHelper(typename RedBlackTree<T>::Node* ptr)
{
    if(ptr == NILL)
    {
        return;
    }
    if(ptr->left != NILL)
    {
        clearHelper(ptr->left);
    }
    if(ptr->right != NILL)
    {
        clearHelper(ptr->right);
    }
    if(ptr->parent)
    {
        if(ptr == ptr->parent->left)
        {
            ptr->parent->left = NILL;
        } else {
            ptr->parent->right = NILL;
        }
        delete ptr;
    }
}

#endif /* _RED_BLACK_TREE_HPP_ */
