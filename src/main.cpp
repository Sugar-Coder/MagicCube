#include "utility.h"

#include "stb_image.h"
#include "Shader.hpp"
#include "cube.h"
#include "drawer.h"
#include "recover.h"

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

    recover Recover;

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube::block), cube::block, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));

    unsigned int texture1 = LoadTexture("../GLSL/container2.png"); // 把工作路径设置为bin达到和终端一样的效果
    Shader cubeShader("../GLSL/shader.vs", "../GLSL/shader.fs"); // ../GLSL/shader.fs 在命令行运行时用相对路径
    cubeShader.use();
    cubeShader.setInt("texture1", 0);

    glEnable(GL_DEPTH_TEST);

    // 灯的着色器
    Shader lampShader("../GLSL/lamp.vs", "../GLSL/lamp.fs");
    unsigned int lightVAO;
    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);
    // 只需要绑定VBO不用再次设置VBO的数据，因为箱子的VBO数据中已经包含了正确的立方体顶点数据
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // 设置灯立方体的顶点属性（对我们的灯来说仅仅只有位置数据）
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // skybox VAO
    unsigned int skyboxVAO, skyboxVBO;
    glGenVertexArrays(1, &skyboxVAO);
    glGenBuffers(1, &skyboxVBO);
    glBindVertexArray(skyboxVAO);
    glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube3D::skyboxVertices), &cube3D::skyboxVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);   // 由于模仿的纹理坐标与天空盒不同，增加天空盒的纹理坐标skyboxTexCoords
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

    // load textures
    std::vector<std::string> faces
            {
                    "../GLSL/darkskies/darkskies_ft.tga",
                    "../GLSL/darkskies/darkskies_bk.tga",
                    "../GLSL/darkskies/darkskies_dn.tga",
                    "../GLSL/darkskies/darkskies_up.tga",
                    "../GLSL/darkskies/darkskies_rt.tga",
                    "../GLSL/darkskies/darkskies_lf.tga"
            };
    unsigned int cubemapTexture = loadCubemap(faces);

    // skybox's shader
    Shader skyboxShader("../GLSL/skybox.vs", "../GLSL/skybox.fs");
    // configure
    skyboxShader.use();
    skyboxShader.setInt("skybox", 0);

    for(int i = 0; i < RN; i++){
        finish[i] = true;
    }
    float lighty = lightPos.y;

    while (!glfwWindowShouldClose(window)) {
        // input
        // -----
        processInput(window);

        // render
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

        lightPos.y = lighty + 3 * sin(glfwGetTime());

        cubeShader.use();
        // 设置光照有关变量
        cubeShader.setVec3("light.position", lightPos);
        cubeShader.setVec3("viewPos", camera.Position);
        //light properties
        cubeShader.setVec3("light.ambient", 0.9f, 0.9f, 0.9f);
        cubeShader.setVec3("light.diffuse", 0.5f, 0.5f, 0.5f);
        cubeShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);

        // material properties
        cubeShader.setFloat("material.shininess", 64.0f);

        cubeShader.setMat4("view", view);
        cubeShader.setMat4("projection", projection);
        cubeShader.setVec4("ourColor",cube3D::cube::colors[0]);

        glBindVertexArray(VAO);

        if(!finish[U]){
            if(drawer.rotate_U(Cube, cubeShader)){
                finish[U] = true;
                screen = false;
            } else {
                screen = true;
            }
        } else if(!finish[D]){
            if(drawer.rotate_D(Cube, cubeShader)){
                finish[D] = true;
                screen = false;
            } else {
                screen = true;
            }
        } else if(!finish[L]){
            if(drawer.rotate_L(Cube, cubeShader)){
                finish[L] = true;
                screen = false;
            } else {
                screen = true;
            }
        } else if(!finish[R]){
            if(drawer.rotate_R(Cube, cubeShader)){
                finish[R] = true;
                screen = false;
            } else {
                screen = true;
            }
        } else if(!finish[F]){
            if(drawer.rotate_F(Cube, cubeShader)){
                finish[F] = true;
                screen = false;
            } else {
                screen = true;
            }
        } else if(!finish[B]){
            if(drawer.rotate_B(Cube, cubeShader)){
                finish[B] = true;
                screen = false;
            } else {
                screen = true;
            }
        } else if(!finish[Ur]){
            if(drawer.rotate_Ur(Cube, cubeShader)){
                finish[Ur] = true;
                screen = false;
            } else {
                screen = true;
            }
        } else if(!finish[Dr]){
            if(drawer.rotate_Dr(Cube, cubeShader)){
                finish[Dr] = true;
                screen = false;
            } else {
                screen = true;
            }
        } else if(!finish[Lr]){
            if(drawer.rotate_Lr(Cube, cubeShader)){
                finish[Lr] = true;
                screen = false;
            } else {
                screen = true;
            }
        } else if(!finish[Rr]){
            if(drawer.rotate_Rr(Cube, cubeShader)){
                finish[Rr] = true;
                screen = false;
            } else {
                screen = true;
            }
        } else if(!finish[Br]){
            if(drawer.rotate_Br(Cube, cubeShader)){
                finish[Br] = true;
                screen = false;
            } else {
                screen = true;
            }
        } else if(!finish[Fr]){
            if(drawer.rotate_Fr(Cube, cubeShader)){
                finish[Fr] = true;
                screen = false;
            } else {
                screen = true;
            }
        } else if(!finish[RECO]){
            if(Recover.Recovering(drawer, Cube, cubeShader)){  // 完成了复原
                finish[RECO] = true;
                screen = false;
            } else {
                screen = true;
            }
        } else {
            drawer.static_draw(Cube, cubeShader);
        }

        lampShader.use();   // 画一个灯
        lampShader.setMat4("projection", projection);
        lampShader.setMat4("view", view);
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::mat4(1.0f);
        model = glm::translate(model, lightPos);
        model = glm::scale(model, glm::vec3(0.2f));
        lampShader.setMat4("model", model);
        // render the lamp
        glBindVertexArray(lightVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // draw skybox as last
        glDepthFunc(GL_LEQUAL);  // change depth function so depth test passes when values are equal to depth buffer's content
        skyboxShader.use();
        view = glm::mat4(glm::mat3(camera.GetViewMatrix())); // remove translation from the view matrix
        skyboxShader.setMat4("view", view);
        skyboxShader.setMat4("projection", projection);
        // skybox cube
        glBindVertexArray(skyboxVAO);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
        glDepthFunc(GL_LESS); // set depth function back to default

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glDeleteVertexArrays(1, &skyboxVAO);
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &skyboxVBO);

    glfwTerminate();
    return 0;
}