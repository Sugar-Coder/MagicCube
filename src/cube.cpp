//
// Created by Sugars Mac on 2019-11-03.
//

#include "cube.h"
#include <cmath>
#include <iostream>

namespace cube3D{

    // Shader cube::shader("GLSL/shader.vs", "GLSL/shader.fs");

    float cube::block[180] = {
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
            0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    const glm::vec4 cube::colors[7] = {
            glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), // top    (green)
            glm::vec4(0.3f, 0.3f, 1.0f , 1.0f), // bottom (blue)
            glm::vec4( 1.0f, 0.3f, 0.3f , 1.0f), // front  (red)
            glm::vec4( 1.0f, 0.5f, 0.0f , 1.0f), // back   (orange)
            glm::vec4( 1.0f, 1.0f, 0.0f , 1.0f), // left   (yellow)
            glm::vec4( 1.0f, 1.0f, 1.0f , 1.0f), // right  (white)
            glm::vec4( 1.0f, 1.0f, 1.0f , 0.0f)  // frame
    };

    const glm::vec3 cube::init_positions[N] = {
            glm::vec3(0.0f, 0.0f, 1.0f), // 前中1
            glm::vec3(0.0f, 0.0f, -1.0f), // 后中2
            glm::vec3(-1.0f, 0.0f, 0.0f), // 左中3
            glm::vec3(1.0f, 0.0f, 0.0f), // 右中4
            glm::vec3(0.0f, 1.0f, 0.0f), // 上中5
            glm::vec3(0.0f, -1.0f, 0.0f), // 下中6

            glm::vec3(-1.0f, 1.0f, -1.0f), // 顶角0
            glm::vec3(1.0f, 1.0f, -1.0f), // corner1
            glm::vec3(1.0f, 1.0f, 1.0f), // corner2
            glm::vec3(-1.0f, 1.0f, 1.0f), // corner3
            glm::vec3(-1.0f, -1.0f, -1.0f), // 底角4
            glm::vec3(1.0f, -1.0f, -1.0f), // corner 5
            glm::vec3(1.0f, -1.0f, 1.0f), // corner 6
            glm::vec3(-1.0f, -1.0f, 1.0f), // corner7

            glm::vec3(-1.0f, 0.0f, -1.0f), // 中层棱0
            glm::vec3( 1.0f, 0.0f, -1.0f), // edge1
            glm::vec3( 1.0f, 0.0f,  1.0f), // edge2
            glm::vec3(-1.0f, 0.0f,  1.0f), // edge3
            glm::vec3( 0.0f, 1.0f, -1.0f), // 顶层棱4
            glm::vec3( 1.0f, 1.0f,  0.0f), // edge5
            glm::vec3( 0.0f, 1.0f,  1.0f), // edge6
            glm::vec3(-1.0f, 1.0f,  0.0f), // edge7
            glm::vec3( 0.0f,-1.0f, -1.0f), // 顶层棱8
            glm::vec3( 1.0f,-1.0f,  0.0f), // edge9
            glm::vec3( 0.0f,-1.0f,  1.0f), // edgeA
            glm::vec3(-1.0f,-1.0f,  0.0f), // edgeB
    };

    cube::cube(){
        int i = MF;
        for(auto& m : models){
            m = glm::translate(m, init_positions[i]);
            i++;
        }
        for(int i = 0; i < N; i++){
            positions[i] = init_positions[i];
        }
    }

    void cube::pos_round(glm::vec3 &position) {
        // std::cout << "the old position:" << position.x << " " << position.y << " " << position.z << std::endl;
        position.x = round(position.x)/2;
        position.y = round(position.y)/2;
        position.z = round(position.z)/2;
        // std::cout << "the new position:" << position.x << " " << position.y << " " << position.z << std::endl;
    }

    /* rotate a face 90 * count degree clockwise */
    void cube::rotate_cube(cube3D::face_type t, int count) { // 更新旋转后的魔方
        glm::vec3 mask;
        glm::mat4 temp_model = glm::mat4(1.0f);
        switch(t){
            case top:
                temp_model = glm::rotate(temp_model, glm::radians(count * -90.0f), y_axis); // 绕y轴顺时针
                mask = glm::vec3(0.0f, 1.0f, 0.0f);  // y坐标是1
                break;
            case bottom:
                temp_model = glm::rotate(temp_model, glm::radians(count * 90.0f), y_axis);
                mask = glm::vec3(0.0f, 1.0f, 0.0f);
                break;
            case front:
                temp_model = glm::rotate(temp_model, glm::radians(count * -90.0f), z_axis);
                mask = glm::vec3(0.0f, 0.0f, 1.0f);
                break;
            case back:
                temp_model = glm::rotate(temp_model, glm::radians(count * 90.0f), z_axis);
                mask = glm::vec3(0.0f, 0.0f, -1.0f);
                break;
            case left:
                temp_model = glm::rotate(temp_model, glm::radians(count * 90.0f), x_axis);
                mask = glm::vec3(-1.0f, 0.0f, 0.0f);
                break;
            case right:
                temp_model = glm::rotate(temp_model, glm::radians(count * -90.0f), x_axis);
                mask = glm::vec3(1.0f, 0.0f, 0.0f);
                break;
            default:
                return;
        }
        for(int i = MF; i <= EB; i++){
            if(mask.x != 0){ // 对于需要旋转的
                if(positions[i].x == mask.x) {
                    models[i] = temp_model * models[i];  // 将变换记录到models
                    positions[i] = models[i] * glm::vec4(init_positions[i], 1.0f);
                    pos_round(positions[i]);
                }
            } else if(mask.y != 0){
                if(positions[i].y == mask.y) {
                    models[i] = temp_model * models[i];
                    positions[i] = models[i] * glm::vec4(init_positions[i], 1.0f);
                    pos_round(positions[i]);
                }
            } else if(mask.z != 0){
                if(positions[i].z == mask.z){
                    models[i] = temp_model * models[i];
                    positions[i] = models[i] * glm::vec4(init_positions[i], 1.0f);
                    pos_round(positions[i]);
                }
            }
        }
    }

    glm::mat4 cube::get_model(int b) {
        return this->models[b];
    }

    glm::vec3 cube::get_position(int b) const {  // 返回当前位置
        return this->positions[b];
    }

    void cube::draw(Shader& shader, const glm::mat4 &model) {
        shader.setMat4("model", model);
    }
}