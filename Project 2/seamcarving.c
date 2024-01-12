/*
ESC 190 Project 2
Completed With: Alex Cho
*/


#include "seamcarving.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void calc_energy(struct rgb_img *im, struct rgb_img **grad){
    create_img(grad, im->height, im->width);    
    for (int y = 0; y < im->height; y++){
        for (int x = 0; x < im->width; x++){
            int rx, gx, bx, ry, gy, by = 0;
            int grady, gradx = 0;
            int energy = 0;

            ry = get_pixel(im, (y+1)%(im->height), x, 0) - get_pixel(im, (y-1+im->height)%(im->height), x, 0);
            gy = get_pixel(im, (y+1)%(im->height), x, 1) - get_pixel(im, (y-1+im->height)%(im->height), x, 1);
            by = get_pixel(im, (y+1)%(im->height), x, 2) - get_pixel(im, (y-1+im->height)%(im->height), x, 2);
            rx = get_pixel(im, y, (x+1)%(im->width), 0) - get_pixel(im, y, (x-1+im->width)%(im->width), 0);
            gx = get_pixel(im, y, (x+1)%(im->width), 1) - get_pixel(im, y, (x-1+im->width)%(im->width), 1);
            bx = get_pixel(im, y, (x+1)%(im->width), 2) - get_pixel(im, y, (x-1+im->width)%(im->width), 2);

            grady = (pow(ry, 2) + pow(gy, 2) + pow(by, 2));
            gradx = (pow(rx, 2) + pow(gx, 2) + pow(bx, 2));
            energy = (int)pow((grady+gradx), 0.5)/10;
            uint8_t e = (uint8_t)energy;
            set_pixel(*grad, y, x, e, e, e);
        }
    }
}

void dynamic_seam(struct rgb_img *grad, double **best_arr){
    
    *best_arr = (double*)malloc(sizeof(double)*(grad->height)*(grad->width));

    for (int y = 0; y < grad->height; y++){
        for (int x = 0; x < grad->width; x++){
            if (y == 0){
                (*best_arr)[x] = (int)get_pixel(grad, 0, x, 0);
            }
            else if (y != 0 && x==0){
                (*best_arr)[y*grad->width+x] = get_pixel(grad, y, x, 0) + fmin((*best_arr)[(y-1)*grad->width+x], (*best_arr)[(y-1)*grad->width+x+1]);
            }

            else if (y != 0 && x==grad->width){
                (*best_arr)[y*grad->width+x] = get_pixel(grad, y, x, 0) + fmin((*best_arr)[(y-1)*grad->width+x], (*best_arr)[(y-1)*grad->width+x-1]);
            }

            else if (y != 0 && x!=0 && x!=grad->width){
                (*best_arr)[y*grad->width+x] = get_pixel(grad, y, x, 0) + fmin(fmin((*best_arr)[(y-1)*grad->width+x], (*best_arr)[(y-1)*grad->width+x+1]), fmin((*best_arr)[(y-1)*grad->width+x], (*best_arr)[(y-1)*grad->width+x-1]));
            }
        }
    }
}

void recover_path(double *best, int height, int width, int **path){
    *path = (int*)malloc(sizeof(int)*(width));
    int minval = 999999;
    int idx = 0;
    for (int x = 0; x < width; x++){
            if (best[x] < minval){
                minval = best[x];
                idx = x;
            }
        }
    (*path)[0] = idx;

    for (int y = 1; y < height; y++){
        int val = fmin(fmin(best[(y)*width+idx], best[(y)*width+idx+1]), fmin(best[(y)*width+idx], best[(y)*width+idx-1]));
        if (val == best[(y)*width+idx-1]){
            idx -= 1;
            (*path)[y] = idx;
        }
        else if (val == best[(y)*width+idx]){
            (*path)[y] = idx;
        }
        else if (val == best[(y)*width+idx+1]){
            idx += 1;
            (*path)[y] = idx;
        }
    }
}

void remove_seam(struct rgb_img *src, struct rgb_img **dest, int *path){
    create_img(dest, src->height, src->width-1);  
    for (int y = 0; y < src->height; y++){
        for (int x = 0; x < src->width; x++){  
            if (x < path[y]){
                set_pixel(*dest, y, x, get_pixel(src, y, x, 0), get_pixel(src, y, x, 1), get_pixel(src, y, x, 2));
            }
            else if(x > path[y]){
                set_pixel(*dest, y, x-1, get_pixel(src, y, x, 0), get_pixel(src, y, x, 1), get_pixel(src, y, x, 2));
            }
        }
    }
}

int main(){
    struct rgb_img *grad;
     struct rgb_img *cur_im;
    struct rgb_img *im;
    double *best;
    int *path;
    read_in_img(&im, "HJoceanSmall.bin");
    calc_energy(im,  &grad);
    dynamic_seam(grad, &best);
    recover_path(best, grad->height, grad->width, &path);
    remove_seam(im, &cur_im, path);
}  