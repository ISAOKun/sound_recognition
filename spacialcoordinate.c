#include <stdio.h>
#include <math.h>
float s_p[];
// 内积
float inner_product(float x1[], float x2[], int dim){
    float value = 0;
    for (int i = 0; i < dim; ++i){
        value = value + x1[i]*x2[i];
    }
    return value;
}

float* spatial_coordinate(float d_t[]){
    float A=0, B=0, C=0;
    float m_p[][3]={ {1, 0.0, 0.0}, {0.0, 1, 0.0}, {0.0, 0.0, 1}};//麦克风坐标，使用这个坐标所得M为单位矩阵方便后续计算
    float delta[3]={0.0, 0.0, 0.0};//声源坐标，中间变量，延时
    float d_d =0 , d_del =0 , del_del =0 , distance =0 ;//内积&距离
     for (int i = 0; i < 3; ++i ){
        s_p[i] = 0;
        d_t[i] = 340*d_t[i];
        delta[i] = 1 - d_t[i];
    }

    d_d     = inner_product(d_t, d_t, 3);
    d_del   = inner_product(delta, d_t, 3);
    del_del = inner_product(delta, delta, 3);    
    A = 4-4*d_d;
    B = 4*d_del;
    C = -del_del;
    distance = (-B-sqrt(pow(B,2)-4*A*C))/2/A;
    
    for (int i = 0; i < 3; ++i){
        s_p[i] = 0.5*(delta[i]-distance*d_t[i]);
    }
    
    return s_p;
}

int main(){
    float u[] = {0.001, 0.001, 0.001};
    float ret[3];
    spatial_coordinate(u);
    for (int i = 0; i < 3; ++i ){
        printf("%f  ",s_p[i]);
    }
    return 0;
}


// #include <stdio.h>
// #include <math.h>

// float inner_product(float x1[], float x2[], int dim) {
//     float value = 0;
//     for (int i = 0; i < dim; ++i) {
//         value = value + x1[i] * x2[i];
//     }
//     return value;
// }

// void spatial_coordinate(float d_t[], float s_p[]) {
//     float A = 0, B = 0, C = 0;
//     float delta[3] = {0.0, 0.0, 0.0};
//     float d_d = 0, d_del = 0, del_del = 0, distance = 0;

//     for (int i = 0; i < 3; ++i) {
//         d_t[i] = 340 * d_t[i];
//         delta[i] = 1 - d_t[i];
//     }

//     d_d = inner_product(d_t, d_t, 3);
//     d_del = inner_product(delta, d_t, 3);
//     del_del = inner_product(delta, delta, 3);
//     A = 4 - 4 * d_d;
//     B = 4 * d_del;
//     C = -del_del;
//     distance = (-B - sqrt(pow(B, 2) - 4 * A * C)) / 2 / A;

//     for (int i = 0; i < 3; ++i) {
//         s_p[i] = 0.5 * (delta[i] - distance * d_t[i]);
//     }
// }

// int main() {
//     float d_t[3] = {0.001, 0.001, 0.001};
//     float s_p[3];
//     spatial_coordinate(d_t, s_p);

//     // 打印结果
//     printf("Spatial coordinates (s_p): %.6f, %.6f, %.6f\n", s_p[0], s_p[1], s_p[2]);

//     return 0;
// }