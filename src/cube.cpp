//
// Created by Sugars Mac on 2019-11-03.
//

#include "cube.h"
#include <cmath>
#include <vector>
#include <bitset>

namespace cube3D{

    float cube::block[180] = {
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // back
            0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  // front
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // left
            -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

            0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // right
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // down
            0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // up
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    const glm::vec4 cube::colors[7] = {
            glm::vec4( 1.0f, 1.0f, 0.2f , 1.0f), // up   (yellow)
            glm::vec4( 1.0f, 1.0f, 1.0f , 1.0f), // bottom  (white)
            glm::vec4( 1.0f, 0.3f, 0.3f , 1.0f), // right  (red)
            glm::vec4( 1.0f, 0.5f, 0.0f , 1.0f), // left   (orange)
            glm::vec4(0.3f, 0.3f, 1.0f , 1.0f), // front (blue)
            glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), // back    (green)
            glm::vec4( 1.0f, 1.0f, 1.0f , 0.0f)  // no
    };

    const glm::vec3 cube::init_positions[N] = {
            glm::vec3(0.0f, 0.0f, 1.0f), // 前中1
            glm::vec3(0.0f, 0.0f, -1.0f), // 后中2
            glm::vec3(-1.0f, 0.0f, 0.0f), // 左中3
            glm::vec3(1.0f, 0.0f, 0.0f), // 右中4
            glm::vec3(0.0f, 1.0f, 0.0f), // 上中5
            glm::vec3(0.0f, -1.0f, 0.0f), // 下中6

            glm::vec3(-1.0f, -1.0f, -1.0f), // 底角0
            glm::vec3(1.0f, -1.0f, -1.0f), // corner 1
            glm::vec3(1.0f, -1.0f, 1.0f), // corner 2
            glm::vec3(-1.0f, -1.0f, 1.0f), // corner3
            glm::vec3(-1.0f, 1.0f, -1.0f), // 顶角4
            glm::vec3(1.0f, 1.0f, -1.0f), // corner5
            glm::vec3(1.0f, 1.0f, 1.0f), // corner6
            glm::vec3(-1.0f, 1.0f, 1.0f), // corner7

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

    /* rotate a face 90 * count degree clockwise(look at the exact face */
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
                mask = glm::vec3(0.0f, -1.0f, 0.0f);
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

    glm::mat4 cube::get_model(int b) const {
        return this->models[b];
    }

    glm::vec3 cube::get_position(int b) const {  // 返回当前位置
        return this->positions[b];
    }

    // 画block_index的小块
    void cube::draw(Shader& shader, const glm::mat4 &model, int block_index) const{
        //        MF, MB, ML, MR, MU, MD,
        //        C0, C1, C2, C3, C4, C5, C6, C7,
        //        E0, E1, E2, E3, E4, E5, E6, E7, E8, E9, EA, EB
        //    前蓝 后绿 左橙 右红 下白 上黄
        static std::vector<std::bitset<6> > map ={
                0x10,0x20,0x08,0x04,0x01,0x02,
                0x2A,0x26,0x16,0x1A, 0x29,0x25,0x15,0x19,
                0x28,0x24,0x14,0x18, 0x21,0x05,0x11,0x09, 0x22, 0x06, 0x12, 0x0a
        };
        shader.setMat4("model", model);
        std::bitset<6> curmap = map[block_index];
        glm::vec4 color;
        for(int i = 5;i >= 0;i--){
            if(curmap[i] != 0){
                color = colors[i];
            } else {
                color = colors[6];
            }
            shader.setVec4("ourColor", color);
            glDrawArrays(GL_TRIANGLES, (5-i) * 6, 6);
        }
    }
}