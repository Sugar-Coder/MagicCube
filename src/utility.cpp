//
// Created by Sugars Mac on 2019-11-07.
//

#include "utility.h"
#include "stb_image.h"  // 加载图片
#include "recover.h"

float lastX = SCR_WIDTH / 2.0f, lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

Camera camera(glm::vec3(0.0f, 3.0f, 6.0f));  // 仅传入相机位置

// timing
float deltaTime = 0.0f; // 当前帧与上一帧的时间差
float lastFrame = 0.0f; // 上一帧的时间

bool screen = false; // 无屏蔽
bool finish[RN] = {true};

void processInput(GLFWwindow *window) {
    recover Recover;
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    // float cameraSpeed = 2.5f * deltaTime;  // 现在在camera类中完成帧延时
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        // cameraPos += cameraSpeed * cameraFront;  // 大小 乘 方向
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        // cameraPos -= cameraSpeed * cameraFront;
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)  // 通过叉乘生成左右横溢效果
        // cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        //cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
        camera.ProcessKeyboard(RIGHT, deltaTime);
    if (!screen){
        if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS){ // 上面(键盘U控制）
            screen = true;
            finish[U] = false;
            Recover.get_rotate(U);
        }
        if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS){  // 下面（键盘J控制）
            screen = true;
            finish[D] = false;
            Recover.get_rotate(D);
        }
        if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS){  // 左面（键盘K控制）
            screen = true;
            finish[L] = false;
            Recover.get_rotate(L);
        }
        if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS){ // 右面（键盘L控制）
            screen = true;
            finish[R] = false;
            Recover.get_rotate(R);
        }
        if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS){ // 正面（键盘I控制）
            screen = true;
            finish[F] = false;
            Recover.get_rotate(F);
        }
        if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS){ // 正面（键盘I控制）
            screen = true;
            finish[B] = false;
            Recover.get_rotate(B);
        }
        if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS){ // 上面逆向(Y）
            screen = true;
            finish[Ur] = false;
            Recover.get_rotate(Ur);
        }
        if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS){
            screen = true;
            finish[Dr] = false;
            Recover.get_rotate(Dr);
        }
        if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS){
            screen = true;
            finish[Lr] = false;
            Recover.get_rotate(Lr);
        }
        if (glfwGetKey(window, GLFW_KEY_SEMICOLON) == GLFW_PRESS){
            screen = true;
            finish[Rr] = false;
            Recover.get_rotate(Rr);
        }
        if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS){
            screen = true;
            finish[Br] = false;
            Recover.get_rotate(Br);
        }
        if (glfwGetKey(window, GLFW_KEY_8) == GLFW_PRESS){
            screen = true;
            finish[Fr] = false;
            Recover.get_rotate(Fr);
        }
        if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS){
            screen = true;
            finish[RECO] = false;
        }
    }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow * window, double xpos, double ypos) {
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX; // 向左offset为负
    float yoffset = lastY - ypos; // 向下offset为负 reversed since y-coordinates go from bottom to top
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.05f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    camera.ProcessMouseScroll(yoffset);
}

unsigned int LoadTexture(std::string filepath){
    stbi_set_flip_vertically_on_load(true);
    unsigned int textureID;
    glGenTextures(1, &textureID);
    // load image, create texture and generate mipmaps
    int width, height, nrComponents;
    // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
    unsigned char *data = stbi_load(filepath.c_str(), &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);  // 释放图像内存
    return textureID;
}

void printVec3(glm::vec3& v){
    if(v.z < 1.0e-4)
        v.z = 0;
    std::cout << v.x << " " << v.y << " " << v.z  << std::endl;
}

void printMat4(glm::mat4& m){
    for(int i = 0; i < 4;i++){
        for(int j=0; j < 4;j++){
            if(m[j][i] < 1.0e-2)
                m[j][i] = 0;
            std::cout << m[j][i] << " ";
        }
        std::cout <<std::endl;
    }
}