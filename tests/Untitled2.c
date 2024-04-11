#include <stdio.h>
#include <string.h>

int main(){

    char used_words[5][20];
    char final_word[20];
    char words[5][20] = {"hell", "what", "ghh", "next"};

    strcpy(final_word,words[0]);

    for(int x = 0; x < 3 ; x++){

        strcpy(used_words[x],words[x+1]);

    }

    for(int x = 0; x < 5; x++){

        printf("%s\n", used_words[x]);
    }

    printf("final %s", final_word);
}
