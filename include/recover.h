//
// Created by Sugars Mac on 2019/12/3.
//

#ifndef MAGICCUBE_RECOVER_H
#define MAGICCUBE_RECOVER_H

#include <vector>
#include "drawer.h"
#include "Shader.hpp"
#include "cube.h"


class recover {
private:
    enum rotate_type {
        R, L, U, D, F, B, Rr, Lr, Ur, Dr, Fr, Br
    };
    static std::vector<int> step_record;
public:
    recover();

    void get_rotate(int rotate_action);

    bool Recovering(view_gl::drawer& drawer, cube3D::cube& cube, Shader& shader); // 复原魔方，返回是否完成复原
};

#endif //MAGICCUBE_RECOVER_H
