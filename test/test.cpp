//
// Created by Sugars Mac on 2019/11/9.
//

#include <iostream>
#include <math.h>
#include <bitset>
#include <vector>

using namespace std;
int main(){
    vector<bitset<6> > map = {
            0Xf0,0xff, 0x03
    };
    cout << map[2][1] << " " << map[2][0];
}