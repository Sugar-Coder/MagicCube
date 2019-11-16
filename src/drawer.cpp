//
// Created by Sugars Mac on 2019-11-06.
//

#include "drawer.h"

namespace view_gl {

    const float drawer::ninety_degree = glm::radians(90.0f);

    drawer::drawer(){
        rotate_speed = 0.01f;
        radians = 0.0f;
    }

    drawer::~drawer() {

    }

    void drawer::static_draw(const cube3D::cube& Cube, Shader& shader) {
        for(int i = 0; i < cube3D::N; i++){ // success
            glm::mat4 model = Cube.get_model(i);
            Cube.draw(shader, model, i);
        }
    }

    bool drawer::rotate_U(cube3D::cube &Cube, Shader &shader) {
        if(radians < ninety_degree){ // 转动未完成

            radians += rotate_speed;

            for (int i = 0; i < cube3D::N; i++) {
                if (Cube.get_position(i).y == 1.0f){ // 转动需要转动的小块
                    glm::mat4 model;
                    model = glm::rotate(model, -radians, cube3D::y_axis);
                    model = model * Cube.get_model(i);
                    Cube.draw(shader, model, i);
                } else {
                    Cube.draw(shader, Cube.get_model(i), i); // 其他的按原来画
                }
            }
            return false;
        } else {
            radians = 0.0f;
            Cube.rotate_cube(cube3D::top, 1); // 改变魔方状态, 顶层顺时针旋转90
            return true;
        }
    }

    bool drawer::rotate_Ur(cube3D::cube &Cube, Shader &shader) { // 顶层逆时针旋转
        if(radians < ninety_degree){
            radians += rotate_speed;

            for (int i = 0; i < cube3D::N; i++) {
                if (Cube.get_position(i).y == 1.0f){ // 转动需要转动的小块
                    glm::mat4 model;
                    model = glm::rotate(model, radians, cube3D::y_axis);
                    model = model * Cube.get_model(i);
                    Cube.draw(shader, model, i);
                } else {
                    Cube.draw(shader, Cube.get_model(i), i); // 其他的按原来画
                }
            }
            return false;
        } else {
            radians = 0.0f;
            Cube.rotate_cube(cube3D::top, -1); // 改变魔方状态, 顶层顺时针旋转90
            return true;
        }
    }

    bool drawer::rotate_D(cube3D::cube &Cube, Shader &shader) { // 旋转底层
        if(radians < ninety_degree){ // 转动未完成

            radians += rotate_speed;

            for (int i = 0; i < cube3D::N; i++) {
                if (Cube.get_position(i).y == -1.0f){ // 转动需要转动的小块
                    glm::mat4 model;
                    model = glm::rotate(model, radians, cube3D::y_axis);
                    model = model * Cube.get_model(i);
                    Cube.draw(shader, model, i);
                } else {
                    Cube.draw(shader, Cube.get_model(i), i); // 其他的按原来画
                }
            }
            return false;
        } else {
            radians = 0.0f;
            Cube.rotate_cube(cube3D::bottom, 1); // 改变魔方状态, 底层顺时针旋转90
            return true;
        }
    }

    bool drawer::rotate_Dr(cube3D::cube &Cube, Shader &shader) { // 底层逆时针旋转
        if(radians < ninety_degree){ // 转动未完成

            radians += rotate_speed;

            for (int i = 0; i < cube3D::N; i++) {
                if (Cube.get_position(i).y == -1.0f){ // 转动需要转动的小块
                    glm::mat4 model;
                    model = glm::rotate(model, -radians, cube3D::y_axis);
                    model = model * Cube.get_model(i);
                    Cube.draw(shader, model, i);
                } else {
                    Cube.draw(shader, Cube.get_model(i), i); // 其他的按原来画
                }
            }
            return false;
        } else {
            radians = 0.0f;
            Cube.rotate_cube(cube3D::bottom, -1); // 改变魔方状态, 底层顺时针旋转90
            return true;
        }
    }

    bool drawer::rotate_L(cube3D::cube &Cube, Shader &shader) {
        if(radians < ninety_degree){ // 转动未完成

            radians += rotate_speed;

            for (int i = 0; i < cube3D::N; i++) {
                if (Cube.get_position(i).x == -1.0f){ // 转动需要转动的小块
                    glm::mat4 model;
                    model = glm::rotate(model, radians, cube3D::x_axis);
                    model = model * Cube.get_model(i);
                    Cube.draw(shader, model, i);
                } else {
                    Cube.draw(shader, Cube.get_model(i), i); // 其他的按原来画
                }
            }
            return false;
        } else {
            radians = 0.0f;
            Cube.rotate_cube(cube3D::left, 1); // 改变魔方状态, L面顺时针旋转90
            for(int i = 0; i < cube3D::N; i++) {
                glm::mat4 model = Cube.get_model(i);
                Cube.draw(shader, model, i);
            }
            return true;
        }
    }

    bool drawer::rotate_Lr(cube3D::cube &Cube, Shader &shader) {
        if(radians < ninety_degree){ // 转动未完成

            radians += rotate_speed;

            for (int i = 0; i < cube3D::N; i++) {
                if (Cube.get_position(i).x == -1.0f){ // 转动需要转动的小块
                    glm::mat4 model;
                    model = glm::rotate(model, -radians, cube3D::x_axis);
                    model = model * Cube.get_model(i);
                    Cube.draw(shader, model, i);
                } else {
                    Cube.draw(shader, Cube.get_model(i), i); // 其他的按原来画
                }
            }
            return false;
        } else {
            radians = 0.0f;
            Cube.rotate_cube(cube3D::left, -1); // 改变魔方状态, L面逆时针旋转90
            for(int i = 0; i < cube3D::N; i++) {
                glm::mat4 model = Cube.get_model(i);
                Cube.draw(shader, model, i);
            }
            return true;
        }
    }

    bool drawer::rotate_R(cube3D::cube &Cube, Shader &shader) {
        if(radians < ninety_degree){ // 转动未完成

            radians += rotate_speed;

            for (int i = 0; i < cube3D::N; i++) {
                if (Cube.get_position(i).x == 1.0f){ // 转动需要转动的小块
                    glm::mat4 model;
                    model = glm::rotate(model, -radians, cube3D::x_axis);
                    model = model * Cube.get_model(i);
                    Cube.draw(shader, model, i);
                } else {
                    Cube.draw(shader, Cube.get_model(i), i); // 其他的按原来画
                }
            }
            return false;
        } else {
            radians = 0.0f;
            Cube.rotate_cube(cube3D::right, 1); // 改变魔方状态, R面顺时针旋转90
            for(int i = 0; i < cube3D::N; i++) {
                glm::mat4 model = Cube.get_model(i);
                Cube.draw(shader, model, i);
            }
            return true;
        }
    }

    bool drawer::rotate_Rr(cube3D::cube &Cube, Shader &shader) {
        if(radians < ninety_degree){ // 转动未完成

            radians += rotate_speed;

            for (int i = 0; i < cube3D::N; i++) {
                if (Cube.get_position(i).x == 1.0f){ // 转动需要转动的小块
                    glm::mat4 model;
                    model = glm::rotate(model, radians, cube3D::x_axis);
                    model = model * Cube.get_model(i);
                    Cube.draw(shader, model, i);
                } else {
                    Cube.draw(shader, Cube.get_model(i), i); // 其他的按原来画
                }
            }
            return false;
        } else {
            radians = 0.0f;
            Cube.rotate_cube(cube3D::right, -1); // 改变魔方状态, R面逆时针旋转90
            for(int i = 0; i < cube3D::N; i++) {
                glm::mat4 model = Cube.get_model(i);
                Cube.draw(shader, model, i);
            }
            return true;
        }
    }

    bool drawer::rotate_F(cube3D::cube &Cube, Shader &shader) {
        if(radians < ninety_degree){ // 转动未完成

            radians += rotate_speed;

            for (int i = 0; i < cube3D::N; i++) {
                if (Cube.get_position(i).z == 1.0f){ // 转动需要转动的小块
                    glm::mat4 model;
                    model = glm::rotate(model, -radians, cube3D::z_axis);
                    model = model * Cube.get_model(i);
                    Cube.draw(shader, model, i);
                } else {
                    Cube.draw(shader, Cube.get_model(i), i); // 其他的按原来画
                }
            }
            return false;
        } else {
            radians = 0.0f;
            Cube.rotate_cube(cube3D::front, 1); // 改变魔方状态, L面顺时针旋转90
            for(int i = 0; i < cube3D::N; i++) {
                glm::mat4 model = Cube.get_model(i);
                Cube.draw(shader, model, i);
            }
            return true;
        }
    }

    bool drawer::rotate_Fr(cube3D::cube &Cube, Shader &shader) {
        if(radians < ninety_degree){ // 转动未完成

            radians += rotate_speed;

            for (int i = 0; i < cube3D::N; i++) {
                if (Cube.get_position(i).z == 1.0f){ // 转动需要转动的小块
                    glm::mat4 model;
                    model = glm::rotate(model, radians, cube3D::z_axis);
                    model = model * Cube.get_model(i);
                    Cube.draw(shader, model, i);
                } else {
                    Cube.draw(shader, Cube.get_model(i), i); // 其他的按原来画
                }
            }
            return false;
        } else {
            radians = 0.0f;
            Cube.rotate_cube(cube3D::front, -1); // 改变魔方状态, L面顺时针旋转90
            for(int i = 0; i < cube3D::N; i++) {
                glm::mat4 model = Cube.get_model(i);
                Cube.draw(shader, model, i);
            }
            return true;
        }
    }

    bool drawer::rotate_B(cube3D::cube &Cube, Shader &shader) {
        if(radians < ninety_degree){ // 转动未完成

            radians += rotate_speed;

            for (int i = 0; i < cube3D::N; i++) {
                if (Cube.get_position(i).z == -1.0f){ // 转动需要转动的小块
                    glm::mat4 model;
                    model = glm::rotate(model, radians, cube3D::z_axis);
                    model = model * Cube.get_model(i);
                    Cube.draw(shader, model, i);
                } else {
                    Cube.draw(shader, Cube.get_model(i), i); // 其他的按原来画
                }
            }
            return false;
        } else {
            radians = 0.0f;
            Cube.rotate_cube(cube3D::back, 1); // 改变魔方状态, L面顺时针旋转90
            for(int i = 0; i < cube3D::N; i++) {
                glm::mat4 model = Cube.get_model(i);
                Cube.draw(shader, model, i);
            }
            return true;
        }
    }

    bool drawer::rotate_Br(cube3D::cube &Cube, Shader &shader) {
        if(radians < ninety_degree){ // 转动未完成

            radians += rotate_speed;

            for (int i = 0; i < cube3D::N; i++) {
                if (Cube.get_position(i).z == -1.0f){ // 转动需要转动的小块
                    glm::mat4 model;
                    model = glm::rotate(model, -radians, cube3D::z_axis);
                    model = model * Cube.get_model(i);
                    Cube.draw(shader, model, i);
                } else {
                    Cube.draw(shader, Cube.get_model(i), i); // 其他的按原来画
                }
            }
            return false;
        } else {
            radians = 0.0f;
            Cube.rotate_cube(cube3D::back, -1); // 改变魔方状态, L面顺时针旋转90
            for(int i = 0; i < cube3D::N; i++) {
                glm::mat4 model = Cube.get_model(i);
                Cube.draw(shader, model, i);
            }
            return true;
        }
    }
}