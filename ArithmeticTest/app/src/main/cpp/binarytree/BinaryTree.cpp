//
// Created by cuiqiang on 18-2-5.
//

#include <stdint.h>
#include "BinaryTree.h"
#include "android/log.h"

static const char *TAG = "jni";
#define LOGD(fmt, args...) __android_log_print(ANDROID_LOG_DEBUG, TAG, fmt, ##args)

BinaryTree::BinaryTree() : node_root_point(NULL) {

}

BinaryTree::~BinaryTree() {

}

void BinaryTree::display() {
    LOGD("Node---------------->%s", "display");
    inOrder(node_root_point);
}

//中序 左中右
void BinaryTree::inOrder(binary_node *node) {
    if (node != NULL) {
        inOrder(node->left_node);
        LOGD("Node---------------->%d", node->key);
        inOrder(node->right_node);
    }
}

/**
 * 删除分三种情况
 * 1.该节点是叶节点
 * 2.该节点有一个子节点
 * 3.该节点右两个子节点
 * 后继节点
 */
bool BinaryTree::detele(int key) {
    if (node_root_point == NULL) {
        return false;
    }
    struct binary_node *node_current = node_root_point;
    struct binary_node *node_parent = node_root_point;
    bool is_left_child = true;
    //判断是根还是左节点,右节点
    while (node_current->key != key) {
        //赋值给父节点
        node_parent = node_current;
        if (key < node_current->key) {
            node_current = node_current->left_node;
            is_left_child = true;
        } else {
            node_current = node_current->right_node;
            is_left_child = false;
        }
        //因为这里跳出循环,所while不执行,此时node_current已经改变,而node_parent还是之前赋值的
        //所以node_parent是父节点
        if (node_current == NULL) {
            return false;
        }
    }

    //叶节点
    if (node_current->left_node == NULL && node_current->right_node == NULL) {
        LOGD("detele---------------->叶节点");
        excute_detele(node_parent, node_current, is_left_child, NULL);
        //有右子节点
    } else if (node_current->left_node == NULL) {
        LOGD("detele---------------->有右子节点");
        excute_detele(node_parent, node_current, is_left_child, node_current->right_node);
        //有左子节点
    } else if (node_current->right_node == NULL) {
        LOGD("detele---------------->有左子节点");
        excute_detele(node_parent, node_current, is_left_child, node_current->left_node);
        //两个字节点,需要找到后继节点
    } else {
        LOGD("detele---------------->有两个子节点");
        //后继节点是 25的后继是30,那么没有比25大还比30小的数
        binary_node *p_successor = node_current;//后继节点
        binary_node *p_parent = node_current;
        binary_node *p_current = node_current->right_node;//临时变量,用寻找后继节点
        //如果有右节点,就需要一直向左找,直到没有
        while (NULL != p_current) {
            p_parent = p_successor;
            p_successor = p_current;
            p_current = p_current->left_node;
        }
        // 后继节点是被删除节点右节点 则 只需要把右子树移到删除的位置
        // 如果不是,则说明是孙节点或更远(因先找右,后左,一定有右,因为判断已经是右两个字节点)
        if (p_successor != node_current->right_node) {
            //父节点的左(原指后继) = 后继节点的右节点(左不可以存在,如果存在继续找左)
            p_parent->left_node = p_successor->right_node;
            //后继(孙)的右节点 = 原来的父节点
            p_successor->right_node = node_current->right_node;
        }
        excute_detele(node_parent, node_current, is_left_child, p_successor);//把被删节点从父节点移除,指向后继节点
        //后继节点的左节点 = 原来删除节点的左节点
        p_successor->left_node = node_current->left_node;
    }
    return true;
}

/**
 *
 * @param p_parent      父节点
 * @param p_current     需要删除的节点
 * @param is_left_child 是否是左节点
 * @param p_node        需要指向的节点
 */
void BinaryTree::excute_detele(binary_node *p_parent, binary_node *p_current, bool is_left_child,
                               binary_node *p_node) {
    LOGD("detele---------------->excute_detele");
    if (p_current == node_root_point) {
        delete node_root_point;
        node_root_point = NULL;
        node_root_point = p_node;
        LOGD("detele---------------->delete node_root_point");
    } else if (is_left_child) {
        delete p_parent->left_node;
        //将被删除的节点的左节点指向到其父节点的左节点上
        p_parent->left_node = p_node;
        LOGD("detele---------------->delete left_node");
    } else {
        delete p_parent->right_node;
        p_parent->right_node = p_node;
        LOGD("detele---------------->delete right_node");
    }
}

string BinaryTree::get(int key) {
    if (node_root_point == NULL) {
        return NULL;
    }
    //修改指针的值,不断修改的这个临时指针的指向,没有修改值
    struct binary_node *node_point = node_root_point;
    while (node_point->key != key) {
        //值小于当前节点的时候,找左节点
        if (key < node_point->key) {
            node_point = node_point->left_node;
        } else {
            node_point = node_point->right_node;
        }
        //赋值后如果是null就返回null
        if (node_point == NULL) {
            return NULL;
        }
    }
    if (node_point == NULL) {
        return NULL;
    } else {
        return node_point->value;
    }
}

void BinaryTree::insert(int key, string value) {
    binary_node *binary_node_point = new binary_node();
    binary_node_point->key = key;
    binary_node_point->value = value;

    //没有根节点就作为根
    if (node_root_point == NULL) {
        node_root_point = binary_node_point;
        LOGD("Node---------------->%d为根", key);
    } else {
        struct binary_node *root_point = node_root_point;
        //声明一个父节点以便插入
        struct binary_node *parent_point;
        //暂不考虑key重复的问题
        while (true) {
            //root_point->parent_node = parent_point;
            //当前节点赋值给父节点,用于更改父节点的引用
            parent_point = root_point;
            if (key > root_point->key) {
                root_point = root_point->right_node;
                if (root_point == NULL) {
                    parent_point->right_node = binary_node_point;
                    LOGD("Node---------------->%d为的%d右节点", key, parent_point->key);
                    return;
                }
            } else {
                root_point = root_point->left_node;
                if (root_point == NULL) {
                    parent_point->left_node = binary_node_point;
                    LOGD("Node---------------->%d为的%d左节点", key, parent_point->key);
                    return;
                }
            }
        }
    }

};