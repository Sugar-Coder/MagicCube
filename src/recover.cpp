//
// Created by Sugars Mac on 2019/12/3.
//

#include "recover.h"

using view_gl::drawer;
using cube3D::cube;

std::vector<int> recover::step_record;  // 类静态变量记得定义

recover::recover() {

}

void recover::get_rotate(int rotate_action) {
    step_record.push_back(rotate_action);
}

bool recover::Recovering(drawer &drawer, cube &cube, Shader& shader) {
    if(step_record.size() > 0){
        switch(step_record.back()){
            case R:
                if(drawer.rotate_Rr(cube, shader)) { // 当前步骤转动完成
                    step_record.pop_back();  // 清空转过的一步
                }
                break;
            case L:
                if(drawer.rotate_Lr(cube, shader)) {
                    step_record.pop_back();
                }
                break;
            case U:
                if(drawer.rotate_Ur(cube, shader)) {
                    step_record.pop_back();
                }
                break;
            case D:
                if(drawer.rotate_Dr(cube, shader)) {
                    step_record.pop_back();
                }
                break;
            case F:
                if(drawer.rotate_Fr(cube, shader)) {
                    step_record.pop_back();
                }
                break;
            case B:
                if(drawer.rotate_Br(cube, shader)) {
                    step_record.pop_back();
                }
                break;
            case Rr:
                if(drawer.rotate_R(cube, shader)) { // 当前步骤转动完成
                    step_record.pop_back();
                }
                break;
            case Lr:
                if(drawer.rotate_L(cube, shader)) {
                    step_record.pop_back();
                }
                break;
            case Ur:
                if(drawer.rotate_U(cube, shader)) {
                    step_record.pop_back();
                }
                break;
            case Dr:
                if(drawer.rotate_D(cube, shader)) {
                    step_record.pop_back();
                }
                break;
            case Fr:
                if(drawer.rotate_F(cube, shader)) {
                    step_record.pop_back();
                }
                break;
            case Br:
                if(drawer.rotate_B(cube, shader)) {
                    step_record.pop_back();
                }
                break;
        }
        return false;  // 还未完成复原
    } else {
        return true;  // 步骤记录中已经全部完成
    }
}