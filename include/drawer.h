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
        const static float ninety_degree;
        float rotate_speed;
        float radians;  // 已经转过的角度
    public:
        drawer();
        ~drawer();
        void static_draw(const cube3D::cube& Cube, Shader& shader);
        bool rotate_U(cube3D::cube& Cube, Shader& shader);
        bool rotate_L(cube3D::cube& Cube, Shader& shader);
        bool rotate_R(cube3D::cube& Cube, Shader& shader);
        bool rotate_D(cube3D::cube& Cube, Shader& shader);
        bool rotate_F(cube3D::cube& Cube, Shader& shader);
        bool rotate_B(cube3D::cube& Cube, Shader& shader);
    };
}


#endif //TESTOPENGL_DRAWER_H
