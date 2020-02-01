//
// Created by Sugars Mac on 2019-11-07.
//

#ifndef MAGICCUBE_UTILITY_H
#define MAGICCUBE_UTILITY_H

#include <string>
#include <iostream>

#include <glad/glad.h>
#include <glfw3.h>

#include "camera.h"

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

extern float lastX, lastY;
extern bool firstMouse;

extern Camera camera;  // 仅传入相机位置

extern glm::vec3 lightPos;  // 世界坐标中光源的位置

// timing
extern float deltaTime; // 当前帧与上一帧的时间差
extern float lastFrame; // 上一帧的时间

extern bool screen; // 屏蔽标志,有键被按下后被设置为true，直到一次旋转完成
const int RN = 12 + 1;  // 多增加一个复原的标志
extern bool finish[RN]; // 按键被按下的标志，R, L, U, D, F, B
// extern bool key_press[RN];   //           u, j, i, k, o, l
enum rotate_type{R, L, U, D, F, B, Rr, Lr, Ur, Dr, Fr, Br, RECO};

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void mouse_callback(GLFWwindow * window, double xpos, double ypos);
void scroll_callback(GLFWwindow * window, double xoffset, double yoffset); // 鼠标滚轮
unsigned int LoadTexture(std::string filepath);
unsigned int loadCubemap(std::vector<std::string> faces);

void printVec3(glm::vec3& v);
void printMat4(glm::mat4& m);

#endif //MAGICCUBE_UTILITY_H
