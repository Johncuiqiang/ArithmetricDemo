# 设置构建本地库所需的最小版本的cbuild。
cmake_minimum_required(VERSION 3.4.1)
# 创建并命名一个库，将其设置为静态
# 或者共享，并提供其源代码的相对路径。
# 您可以定义多个库，而cbuild为您构建它们。
# Gradle自动将共享库与你的APK打包。

add_library( ArithmeticLib  #设置库的名称。即SO文件的名称，生产的so文件为“libhello-lib.so”,在加载的时候“System.loadLibrary("hello-lib");”
             SHARED  # 将库设置为共享库。
             src/main/cpp/Arithmetic.cpp    # 提供一个源文件的相对路径
             src/main/cpp/binarytree/BinaryTree.cpp
             src/main/cpp/redblacktree/RedBlackTree.cpp
             src/main/cpp/binarysearch/BinarySearch.cpp
)


#搜索指定的预构建库，并将该路径存储为一个变量。因为cbuild默认包含了搜索路径中的系统库，所以您只需要指定您想要添加的公共NDK库的名称。cbuild在完成构建之前验证这个库是否存在。
find_library(
             # 设置path变量的名称。
             log-lib
             #  指定NDK库的名称 你想让CMake来定位。
             log
)
target_link_libraries(ArithmeticLib ${log-lib})
