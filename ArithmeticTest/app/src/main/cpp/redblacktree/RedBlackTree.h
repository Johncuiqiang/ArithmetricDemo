//
// Created by cuiqiang on 18-2-5.
//

#ifndef ARITHMETICTEST_REDBLACKTREE_H
#define ARITHMETICTEST_REDBLACKTREE_H
#include <string>
using namespace std;

static const char *TAG = "jni";
#define LOGD(fmt, args...) __android_log_print(ANDROID_LOG_DEBUG, TAG, fmt, ##args)

class RedBlackTree {
     public:
         void insert(int key,string value);
         void display();
         string get(int key);
         RedBlackTree();
         ~RedBlackTree();
     private:
          struct node{
              bool is_red = false;
              int key;
              string value;
              node * parent_node = NULL;
              node * p_left_child = NULL;
              node * p_right_child = NULL;
          };
          node * p_root;
          void inOrder(node * p_node);
          void insertFixUp(node * p_node);
          void leftRotate(node *p_node);
          void rightRotate(node *p_node);
};


#endif //ARITHMETICTEST_REDBLACKTREE_H
