//
// Created by cuiqiang on 18-2-5.
//

#include <android/log.h>
#include "RedBlackTree.h"

RedBlackTree::RedBlackTree() : p_root(NULL) {

}


RedBlackTree::~RedBlackTree() {

}


void RedBlackTree::display() {
    inOrder(p_root);
}

//中序 左中右
void RedBlackTree::inOrder(struct node *p_node) {
    if (p_node != NULL) {
        inOrder(p_node->p_left_child);
        LOGD("Node---------------->%d", p_node->key);
        inOrder(p_node->p_right_child);
    }
}

string RedBlackTree::get(int key) {
    if (p_root == NULL) {
        return NULL;
    }
    struct node *p_node = p_root;
    while (p_node->key != key) {
        if (p_node->key > key) {
            p_node = p_node->p_left_child;
        } else {
            p_node = p_node->p_right_child;
        }
        if (p_node == NULL) {
            return NULL;
        }
    }
    return p_node->value;
}

void RedBlackTree::insert(int key, string value) {
    LOGD("Node---------------->插入%d",key);
    //创建节点
    node *p_node = new node();
    p_node->is_red = true;
    p_node->key = key;
    p_node->value = value;
    //如果根为null
    if (p_root == NULL) {
        p_node->is_red = false;
        p_root = p_node;
        LOGD("Node---------------->%d为根",p_root->key);
        return;
    }
    node *p_temp_node = p_root;
    node *p_parent;

    while (true) {
        p_parent = p_temp_node;
        if (key > p_temp_node->key) {
            p_temp_node = p_temp_node->p_right_child;
            if (p_temp_node == NULL) {
                p_parent->p_right_child = p_node;
                p_node->parent_node = p_parent;
                LOGD("Node---------------->%d为%d的右节点",key,p_parent->key);
                insertFixUp(p_node);
                return;
            }
        } else {
            p_temp_node = p_temp_node->p_left_child;
            if (p_temp_node == NULL) {
                p_parent->p_left_child = p_node;
                p_node->parent_node = p_parent;
                LOGD("Node---------------->%d为%d的左节点",key,p_parent->key);
                insertFixUp(p_node);
                return;
            }
        }

    }
}

//暂时只是按照红黑规则定义,具体原理应该看2-3-4树的节点分裂
void RedBlackTree::insertFixUp(node *p_node) {
    p_node->is_red = true;
    while (p_node != NULL && p_node != p_root && p_node->parent_node->is_red) {
        if (p_node->parent_node == p_node->parent_node->parent_node->p_left_child) {
            node *p_node_y = p_node->parent_node->parent_node->p_right_child;
            //情况1,父节点红,叔叔节点红
            if (p_node_y != NULL && p_node_y->is_red) {
                LOGD("Node---------------->情况1");
                p_node->parent_node->is_red = false;
                p_node_y->is_red = false;
                p_node->parent_node->parent_node->is_red = true;
                p_node = p_node->parent_node->parent_node;
            } else {
                //情况2
               if(p_node == p_node->parent_node->p_right_child){
                   p_node = p_node->parent_node;
                   LOGD("Node---------------->执行左旋");
                   leftRotate(p_node);
               }
                //情况3
                p_node->parent_node->is_red = false;
                p_node->parent_node->parent_node->is_red = true;
                LOGD("Node---------------->执行右旋");
                rightRotate(p_node->parent_node->parent_node);
            }
        } else {
            node *p_node_y = p_node->parent_node->parent_node->p_left_child;
            //情况4
            if (p_node_y != NULL && p_node_y->is_red) {
                LOGD("Node---------------->情况4");
                p_node->parent_node->is_red = false;
                p_node_y->is_red = false;
                p_node->parent_node->parent_node->is_red = true;
                p_node = p_node->parent_node->parent_node;
            } else {
                //情况5
                if(p_node == p_node->parent_node->p_left_child){
                    p_node = p_node->parent_node;
                    LOGD("Node---------------->执行右旋");
                    rightRotate(p_node);
                }
                //情况4
                p_node->parent_node->is_red = false;
                p_node->parent_node->parent_node->is_red = true;
                LOGD("Node---------------->执行左旋");
                leftRotate(p_node->parent_node->parent_node);
            }
        }
    }
    p_root->is_red = false;
}

/**
 *  左旋
 */
void RedBlackTree::leftRotate(node *p_node) {
//  左旋节点要找它的右作为父节点,它的左孩子作为新的右结点
//  1.p_node的右结点 由原来的右结点 改为 它的左孩子
//  2.p_node的父节点改为 它原来的右节点
//  3.p_node要做为它原来右结点的左结点
    //完成第一步
    node *p_node_right_child = p_node->p_right_child;
    p_node->p_right_child = p_node_right_child->p_left_child;

    if (p_node_right_child->p_left_child != NULL)
        p_node_right_child->p_left_child->parent_node = p_node;
    //完成第二步
    p_node_right_child->parent_node = p_node->parent_node;
    //如果p_node的父节点是null,那么p_node_right_child就作为根结点
    if (p_node->parent_node == NULL)
        p_root = p_node_right_child;
    else if (p_node->parent_node->p_left_child == p_node)
        p_node->parent_node->p_left_child = p_node_right_child;
    else
        p_node->parent_node->p_right_child = p_node_right_child;
    //完成第三步
    p_node_right_child->p_left_child = p_node;
    p_node->parent_node = p_node_right_child;

}

/**
 * 右旋
 */
void RedBlackTree::rightRotate(node *p_node) {
    //完成第一步
    node *p_node_left_child = p_node->p_left_child;
    p_node->p_left_child = p_node_left_child->p_right_child;
    if (p_node_left_child->p_right_child != NULL)
        p_node_left_child->p_right_child->parent_node = p_node;
    //完成第二步
    p_node_left_child->parent_node = p_node->parent_node;
    //如果p_node的父节点是null,那么p_node_right_child就作为根结点
    if (p_node->parent_node == NULL)
        p_root = p_node_left_child;
    else if (p_node->parent_node->p_right_child == p_node)
        p_node->parent_node->p_right_child = p_node_left_child;
    else
        p_node->parent_node->p_left_child = p_node_left_child;
    //完成第三步
    p_node_left_child->p_right_child = p_node;
    p_node->parent_node = p_node_left_child;
}