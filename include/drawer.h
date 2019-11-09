//
// Created by Sugars Mac on 2019-11-06.
//

#ifndef TESTOPENGL_DRAWER_H
#define TESTOPENGL_DRAWER_H

#include "utility.h"

#include "Shader.hpp"  // 编译GLSL
#include "cube.h"

namespace view_gl {

    class drawer {
    private:
        cube3D::cube Cube;
        GLFWwindow* window;

        unsigned int VBO, VAO;
        unsigned int texture;
    public:
        drawer();
        ~drawer();
        void init();
        void drawing();

    private:
        void static_draw(Shader& shader);
        //bool dynamic_draw();
    };
}


#endif //TESTOPENGL_DRAWER_H
