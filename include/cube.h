//
// Created by Sugars Mac on 2019-11-03.
//

#ifndef TESTOPENGL_CUBE_H
#define TESTOPENGL_CUBE_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.hpp"  // 编译GLSL

namespace cube3D {

    enum face_type {
        top, bottom, front, back, left, right
    };
    // 用于索引小块块
    enum block_type{
        MF, MB, ML, MR, MU, MD,
        C0, C1, C2, C3, C4, C5, C6, C7,
        E0, E1, E2, E3, E4, E5, E6, E7, E8, E9, EA, EB
    };
    enum color_type{
        green, blue, orange, red ,white, yellow, no
    };

    const static int N = 26;  // 小块个数
    const glm::vec3 z_axis = glm::vec3(0.0f, 0.0f, 1.0f);
    const glm::vec3 x_axis = glm::vec3(1.0f, 0.0f, 0.0f);
    const glm::vec3 y_axis = glm::vec3(0.0f, 1.0f, 0.0f);

    class cube {
    private:
        static const glm::vec3 init_positions[N]; // 26个小块的初始位置
        glm::vec3 positions[N];  // positions[i] = models[i] * vec4(init_positions, 1.0f)
/*
 * observing from the top face, the index of corners will be like this
 *     *-*-*-*        *-*-*-*
 *     |0| |1|        |4| |5|
 *     *-*-*-*        *-*-*-*
 *     | | | |        | | | |
 *     *-*-*-*        *-*-*-*
 *     |3| |2|        |7| |6|
 *     *-*-*-*        *-*-*-*
 * the bottom face, the top face
 *
 * observing from the top face, the index of edges will be like this
 *     *-*-*-*          *-*-*-*         *-*-*-*
 *     | |8| |          |0| |1|         | |4| |
 *     *-*-*-*          *-*-*-*         *-*-*-*
 *     |B| |9|          | | | |         |7| |5|
 *     *-*-*-*          *-*-*-*         *-*-*-*
 *     | |A| |          |3| |2|         | |6| |
 *     *-*-*-*          *-*-*-*         *-*-*-*
 * the bottom face, the middle level, the top face
 *
 * the priority of the key faces: UD > LR > FB
 *
 */
        glm::mat4 models[N];   // 记录每一块的变换矩阵
        static void pos_round(glm::vec3& position);  // 对变换后的坐标取整
    public:
        static const glm::vec4 colors[7]; // 6种魔方标准色和一个透明色
        static float block[180];  // 一个小块的三角形点的坐标，用于渲染
        cube();
        /* rotate a face 90 * count degree clockwise */
        void rotate_cube(face_type t, int count = 1);  // 完成一次变换后更新model和position
        glm::vec3 get_position(int b) const;  // 获得某一块的当前位置
        glm::mat4 get_model(int b) const;
        void draw(Shader& shader, const glm::mat4& model, int block_index) const;
    };

}
#endif //TESTOPENGL_CUBE_H
