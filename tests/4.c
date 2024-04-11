#include <stdio.h>

int main(){

    int n = 5;

    for(int x = 0; x < n; x++){

        for(int y = 0; y < n; y++){


            if( y == 2){

                    y = 1;

                    continue;


            }
            printf("%d, %d\n", x,y);
        }
    }

}
