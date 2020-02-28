# MagicCube
glm库用于做线性代数矩阵运算，一个只有头文件的库，放到usr/local/include<br>
glad.c用于管理OpenGL指针,使用方法见：https://www.jianshu.com/p/891d630e30af<br>
### build
```bash
$mkdir build
$cd build
$cmake ..
$make
$cd ../bin
$./MagicCube
```
A magicCube game that developed for OpenGL and c++ practice<br>
可用键盘控制，旋转魔方，回车复原魔方
### 复原算法1:反着转回来😜
-----
![screenshot](https://github.com/Sugar-Coder/MagicCube/blob/master/rotate.gif)
----
## 增加天空盒：
![skybox](https://tva1.sinaimg.cn/large/006tNbRwgy1gbgrq1nve1j317y0ssnpd.jpg)
