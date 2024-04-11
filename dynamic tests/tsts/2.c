#include <stdio.h>
#include <string.h>


int main(){

    int a = 5;

    while(a == 5){

        char * token = strtok(string, " ");

        while( token != NULL ) {
            printf( " %s\n", token ); //printing each token
            token = strtok(NULL, " ");
        }
    }

    char string[50] = "Hello! We are learning about strtok";
 
    

    return 0;


}