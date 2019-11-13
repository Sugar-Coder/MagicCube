#include "utility.h"

#include "stb_image.h"
#include "Shader.hpp"
#include "cube.h"
#include "drawer.h"

using cube3D::cube;

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "MagicCube", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // 让程序获得鼠标
    glfwSetCursorPosCallback(window, mouse_callback);

    glfwSetScrollCallback(window, scroll_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    cube3D::cube Cube;

    view_gl::drawer drawer;

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube::block), cube::block, GL_STATIC_DRAW);

    // position attribute vs中的位置，属性大小，，，步长，偏移量
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    unsigned int texture1 = LoadTexture("GLSL/container2.png");
    Shader shader("GLSL/shader.vs", "GLSL/shader.fs");
    shader.use();
    shader.setInt("texture1", 0);

    glEnable(GL_DEPTH_TEST);

    bool fini_rota = false;
    float rad2 = 0.0f;
    bool change = false;
    for(int i = 0; i < 6; i++){
        finish[i] = true;
    }
    while (!glfwWindowShouldClose(window)) {
        // input
        // -----
        processInput(window);

        // render
        // ------
        // glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // bind Texture
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);

        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);
        view = camera.GetViewMatrix();
        projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH/(float)SCR_HEIGHT, 0.1f, 100.0f);

        shader.use();
        shader.setMat4("view", view);
        shader.setMat4("projection", projection);
        shader.setVec4("ourColor",cube3D::cube::colors[0]);

        glBindVertexArray(VAO);

        if(!finish[U]){
            if(drawer.rotate_U(Cube, shader)){
                finish[U] = true;
                screen = false;
            } else {
                screen = true;
            }
        } else if(!finish[D]){
            if(drawer.rotate_D(Cube, shader)){
                finish[D] = true;
                screen = false;
            } else {
                screen = true;
            }
        } else if(!finish[L]){
            if(drawer.rotate_L(Cube, shader)){
                finish[L] = true;
                screen = false;
            } else {
                screen = true;
            }
        } else if(!finish[R]){
            if(drawer.rotate_R(Cube, shader)){
                finish[R] = true;
                screen = false;
            } else {
                screen = true;
            }
        } else if(!finish[F]){
            if(drawer.rotate_F(Cube, shader)){
                finish[F] = true;
                screen = false;
            } else {
                screen = true;
            }
        } else if(!finish[B]){
            if(drawer.rotate_B(Cube, shader)){
                finish[B] = true;
                screen = false;
            } else {
                screen = true;
            }
        } else {
            drawer.static_draw(Cube, shader);
        }

/*
        float rotatespeed = 20.0f;
        float radians = (rotatespeed * glm::radians(glfwGetTime()) > glm::radians(90.0f) )? glm::radians(90.0f) : rotatespeed * glm::radians(glfwGetTime());
        if (radians == glm::radians(90.0f) && !change) {  // 第一个旋转结束
            fini_rota = true;
            Cube.rotate_cube(cube3D::bottom, 1); // 改变魔方状态
            change = true; // 魔方状态也改变过了
        }
        if(!fini_rota) {
            for (int i = 0; i < cube3D::N; i++) {
                if (Cube.get_position(i).y == -1) {
                    //std::cout << fini_rota << "test " << std::endl;
                    glm::mat4 model;
                    model = glm::rotate(model, radians, cube3D::y_axis);
                    model = glm::translate(model, Cube.get_position(i));
                    Cube.draw(shader, model, i);
                } else {
                    Cube.draw(shader, Cube.get_model(i), i);
                }
            }
        } else {
            if(rad2 < glm::radians(90.0f))
                rad2 += 0.005;
            else
                rad2 = glm::radians(90.0f);
            for (int i = 0; i < cube3D::N; i++) {
                if (Cube.get_position(i).z == 1.0f){
                    glm::mat4 model;
                    model = glm::rotate(model, rad2, cube3D::z_axis);
                    model = model * Cube.get_model(i);
                    //shader.setMat4("model", model);
                    //glDrawArrays(GL_TRIANGLES, 0, 36);
                    Cube.draw(shader, model, i);
                } else {
                    // shader.setMat4("model", Cube.get_model(i));
                    // glDrawArrays(GL_TRIANGLES, 0, 36);
                    Cube.draw(shader, Cube.get_model(i), i);
                }
            }
        }
        */

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}