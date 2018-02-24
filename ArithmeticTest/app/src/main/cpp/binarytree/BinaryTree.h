//
// Created by cuiqiang on 18-2-5.
//

#ifndef ARITHMETICTEST_BINARYTREE_H
#define ARITHMETICTEST_BINARYTREE_H
#include <string>
using namespace std;

class BinaryTree {

     public:
        typedef struct binary_node{
            int key;
            string value;
            binary_node * left_node = NULL;
            binary_node * right_node = NULL;
        }node;

        BinaryTree();
        ~BinaryTree();
        void insert(int key,string value);
        string get(int key);
        void display();
        bool detele(int key);
     private:
        binary_node * node_root_point;
        void inOrder(binary_node * node);
        void excute_detele(binary_node * p_parent, binary_node * p_current, bool is_left_child,
                           binary_node *p_node);
};


#endif //ARITHMETICTEST_BINARYTREE_H
