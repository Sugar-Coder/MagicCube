# MagicCube
glm库用于做线性代数矩阵运算，一个只有头文件的库，放到usr/local/include<br>
glad.c用于管理OpenGL指针,使用方法见：https://www.jianshu.com/p/891d630e30af<br>
glfw用于创建窗口，使用brew安装，在CMakeList.txt中指定对应头文件和库的位置
### build
```bash
$brew install glfw
$mkdir build
$cd build
$cmake ..
$make
$./MagicCube
```
A magicCube game that developed for OpenGL and c++ practice<br>
可用键盘控制，旋转魔方，回车复原魔方
### 复原算法1:反着转回来😜