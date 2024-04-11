#include <stdio.h>
#include <stdlib.h>

int main(){

    int r=3, c =6;

    int *arr = (int*)malloc(r*c*sizeof(int));


    for(int x = 0; x < r;x++){

        for(int y = 0; y < c; y++){

            printf("num: %d\n", arr[x][y]);
        }
    }

    return 0;
}