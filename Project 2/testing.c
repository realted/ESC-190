#include <stdio.h>
#include <stdlib.h>

int main(){
    int*arr = (int*)malloc(5*sizeof(int));
    int res = sizeof(arr[6]);
    printf("%d", res);
}


// Part 1 test
//print_grad(grad);


// Part 2 test
/*
    for (int i = 0; i<(grad->height); i++){
        for (int j = 0; j<(grad->width); j++){
            printf("%f ", best[i*grad->width+j]);
        }
        printf("\n");
    }
    */



// Part 3 test

/*
for (int i = 0; i<(grad->height); i++){
        printf("%d\n", path[i]);
    }

*/



/*
for (int y = 0; y < height; y++){
        int minval = 999999;
        int idx = 0;
        for (int x = 0; x < width; x++){
            if (best[y*width+x] < minval){
                minval = best[y*width+x];
                idx = x;
            }
        }
        (*path)[y] = idx;
    }*/