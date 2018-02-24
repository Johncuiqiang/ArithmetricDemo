//
// Created by cuiqiang on 18-2-4.
//
#include "../jni/cuiqiang_ling_ai_arithmetic_MainActivity.h"
#include "jni.h"
#include "android/log.h"
#include "binarytree/BinaryTree.h"
#include "redblacktree/RedBlackTree.h"
using namespace std;

#define LOGD(fmt, args...) __android_log_print(ANDROID_LOG_DEBUG, TAG, fmt, ##args)
#define LOGE(fmt, args...) __android_log_print(ANDROID_LOG_ERROR, TAG, fmt, ##args)

JNIEXPORT jstring JNICALL Java_cuiqiang_ling_ai_arithmetic_MainActivity_getStr
        (JNIEnv *env, jobject jobject){
//    BinaryTree *tree = new BinaryTree();
//    tree->insert(10,"2");
//    tree->insert(6,"3");
//    tree->insert(12,"8");
//    tree->insert(3,"8");
//    tree->insert(8,"456");
//    tree->insert(14,"123");
//    tree->insert(11,"8");
//    tree->display();
//
//    string key = tree->get(11);
//    LOGD("Node---------------->%s",key.c_str());
//
//    string value = tree->get(12);
//    LOGD("Node---------------->%s",value.c_str());
//    tree->detele(6);
//    tree->display();
//    delete tree;

    RedBlackTree *tree = new RedBlackTree();
    tree->insert(15,"15");
    tree->insert(27,"27");
    tree->insert(31,"31");
    tree->insert(7,"7");
    tree->insert(8,"8");
    tree->insert(9,"9");
    tree->insert(18,"18");
    tree->display();
    LOGD("Node---------------->%s",tree->get(9).c_str());
    return env->NewStringUTF("你好");
}