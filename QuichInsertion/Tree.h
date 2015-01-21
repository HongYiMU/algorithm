#ifndef TREE_H
#define TREE_H

template<typename T>
class BinaryNode
{
public:
       T data;
       BinaryNode<T>* lchild;
       BinaryNode<T>* rchild;             
}

#endif
