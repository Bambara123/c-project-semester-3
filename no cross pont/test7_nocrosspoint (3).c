#include <stdio.h>
#include <string.h>

typedef struct _ {

    int row;
    int colo;
    int length;
    int word_fill_count;
    char direction; // 'v' - vertical, 'h' - horizontal
    char words_filled[10][20];
    char fill_word[20];

} word_space;

word_space array[100];
word_space array_v[100];
word_space combined_array[100];
int used_word_bool[100] = { };
char used_words[5][20];

int main(){

    char word_list[7][20] = {"cat","ants"};

    char puzzle_array[5][5] = {"*****","*###*","**#**","**#**","**#**"};
    int word_space_array_count = 0;

    for(int x = 0; x < 5; x++){

        int word_length = 0;
        int start_row, start_colo; // make these 0 if didn't work.
        int counting_started = 0;
        int counting_enabled = 0;

        for(int y = 0; y < 5; y ++){

            if(puzzle_array[x][y] == '#' && counting_started == 0){ // finding first #.
                word_length++;
                counting_started = 1;
                counting_enabled = 1;
                start_row = x;
                start_colo = y;

            }else if(puzzle_array[x][y] == '#' && counting_enabled == 1){ // What happens after found first # and count.
                word_length++;

            }else if(puzzle_array[x][y]== '*'){ // what happens when * is there
                counting_started = 0;
                counting_enabled = 0;

                if(word_length > 1){ // If * is encountered, check for a word space.

                    array[word_space_array_count].row = start_row;
                    array[word_space_array_count].colo = start_colo;
                    array[word_space_array_count].length = word_length;
                    array[word_space_array_count].direction = 'h';

                    word_space_array_count++;
                }
                word_length = 0;

            }
        }

        if(word_length > 1){ //  At the end of the row, check for a word space.

            array[word_space_array_count].row = start_row;
            array[word_space_array_count].colo = start_colo;
            array[word_space_array_count].length = word_length;
            array[word_space_array_count].direction = 'h';


            word_space_array_count++;


        }
    }

// -------------------------------------------------------------------------------------------------------------------- vertical
    int word_space_array_count_v = 0;

    for(int x = 0; x < 5; x++){

        int word_length_v = 0;
        int start_row_v, start_colo_v; // make these 0 if didn't work.
        int counting_started_v = 0;
        int counting_enabled_v = 0;

        for(int y = 0; y < 5; y ++){

            if(puzzle_array[y][x] == '#' && counting_started_v == 0){
                word_length_v++;
                counting_started_v = 1;
                counting_enabled_v = 1;
                start_row_v = y;
                start_colo_v = x;

            }else if(puzzle_array[y][x] == '#' && counting_enabled_v == 1){
                word_length_v++;

            }else if(puzzle_array[y][x]== '*'){
                counting_started_v = 0;
                counting_enabled_v = 0;

                if(word_length_v > 1){

                    array_v[word_space_array_count_v].row = start_row_v;
                    array_v[word_space_array_count_v].colo = start_colo_v;
                    array_v[word_space_array_count_v].length = word_length_v;
                    array_v[word_space_array_count_v].direction = 'v';

                    word_space_array_count_v++;

                }
                word_length_v = 0;

            }
        }

        if(word_length_v > 1){

            array_v[word_space_array_count_v].row = start_row_v;
            array_v[word_space_array_count_v].colo = start_colo_v;
            array_v[word_space_array_count_v].length = word_length_v;
            array_v[word_space_array_count_v].direction = 'v';

            word_space_array_count_v++;
        }
    }

    int c_a_count = 0; // combine horizontal and vertical arrays.

    for(int x = 0; x < word_space_array_count; x++){

        combined_array[x] = array[x];
        c_a_count = x;
    }

    for (int x = 0; x < word_space_array_count_v; x++){

        combined_array[c_a_count + 1 + x] = array_v[x];

    }

    c_a_count = word_space_array_count + word_space_array_count_v; // elements in combined array.

// -------------------------------------------------------------------------------------------------------------------------------- // filling spaces.

    for(int x = 0; x < c_a_count; x++){

        for(int y = 0; y < 4; y++){ // 4 = length of the word list.

            int word_filled_ind = 0;

            for(int w = 0; w < combined_array[x].word_fill_count; w++){ // check till end of all filled words in the words filled array of the space.

                if(strcmp(word_list[y], combined_array[x].words_filled[combined_array[x].word_fill_count]) != 0){

                    word_filled_ind++;
                }
            }

            if(word_filled_ind == combined_array[x].word_fill_count){

                if(strlen(word_list[y]) == combined_array[x].length  && used_word_bool[y] == 0){

                    if(combined_array[x].direction == 'h'){ // fill horizontally.

                        int non_hash_count = 0;
                        int letter_count = 0;

                        for(int z = 0; z < combined_array[x].length; z++){

                            if(puzzle_array[combined_array[x].row][combined_array[x].colo + z] != '#'){

                                non_hash_count++;

                                if(puzzle_array[combined_array[x].row][combined_array[x].colo + z] == word_list[y][z]){

                                    letter_count++;
                                }
                            }
                        }

                        if(letter_count == non_hash_count){

                            printf("found x = %d, y = %d\n",x,y);
                            for(int i = 0; i < combined_array[x].length; i++){

                                if(puzzle_array[combined_array[x].row][combined_array[x].colo + i] == '#'){

                                    puzzle_array[combined_array[x].row][combined_array[x].colo + i] = word_list[y][i];
                                    strcpy(combined_array[x].words_filled[combined_array[x].word_fill_count], word_list[y]);
                                    printf("horizontal element: %c\n",puzzle_array[combined_array[x].row][combined_array[x].colo + i]);

                                }
                            }

                            used_word_bool[y] = 1;
                            combined_array[x].word_fill_count++;

                        }
                    }

                    if(combined_array[x].direction == 'v'){// filling vertically.

                        int non_hash_count = 0;
                        int letter_count = 0;

                        for(int z = 0; z < combined_array[x].length; z++){

                            if(puzzle_array[combined_array[x].row + z][combined_array[x].colo] != '#'){

                                printf("ok");
                                non_hash_count++;

                                if(puzzle_array[combined_array[x].row + z ][combined_array[x].colo] == word_list[y][z]){
                                    printf("ok");
                                    letter_count++;
                                }
                            }
                        }

                        if(letter_count == non_hash_count){

                            printf("found\n");
                            for(int i = 0; i < combined_array[x].length; i++){

                                if(puzzle_array[combined_array[x].row + i][combined_array[x].colo] == '#'){ // We don't fill once we fill the letter.

                                    puzzle_array[combined_array[x].row + i][combined_array[x].colo] = word_list[y][i];
                                    strcpy(combined_array[x].words_filled[combined_array[x].word_fill_count], word_list[y]);
                                    printf("element: %c\n",puzzle_array[combined_array[x].row + i][combined_array[x].colo]);
                                    printf("went_v\n");
                                }
                            }
                            used_word_bool[y] = 1;
                            combined_array[x].word_fill_count++;

                        }
                    }
                }
            }
        }
    }

    for(int x = 0; x < 5; x++){ // printing the array.

        for(int y = 0; y < 5; y++){

           printf("%c", puzzle_array[x][y]);
        }

        printf("\n");
    }

    printf("%d\n",combined_array[0].word_fill_count);
    printf("%d\n",combined_array[1].word_fill_count);
    printf("%s\n",combined_array[0].words_filled[0]);
    printf("%s\n",combined_array[1].words_filled[0]);

    return 0;
}
