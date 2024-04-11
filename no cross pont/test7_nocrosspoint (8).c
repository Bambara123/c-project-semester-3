#include <stdio.h>
#include <string.h>

#define word_array_size 14
#define puzzle_row 10
#define puzzle_colo 10


typedef struct _ {

    int row;
    int colo;
    int length;
    int word_fill_count;
    char direction; // 'v' - vertical, 'h' - horizontal
    char words_filled[20][20];

    int index_x[100]; // for getting indexes
    int index_y[100];
    int filled_index_index;

} word_space;

word_space array[100];
word_space array_v[100];
word_space combined_array[100];

int used_word_bool[100] = { };

int main(){

    char word_list[word_array_size][20] = {"nml","ymw","yrze","krl","petv","pd","th","mve","hell","mgh","sg","kveh","lk","se"};

    char puzzle_array[puzzle_row][puzzle_colo] = {"**#*##","*###*#","###*##","*#*###","####**","#*####"};
    int word_space_array_count = 0;

    for(int x = 0; x < puzzle_row; x++){

        int word_length = 0;
        int start_row, start_colo; // make these 0 if didn't work.
        int counting_started = 0;
        int counting_enabled = 0;

        for(int y = 0; y < puzzle_colo; y ++){

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

    for(int x = 0; x < puzzle_row; x++){

        int word_length_v = 0;
        int start_row_v, start_colo_v; // make these 0 if didn't work.
        int counting_started_v = 0;
        int counting_enabled_v = 0;

        for(int y = 0; y < puzzle_colo; y ++){

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

        int words_tested = 0, no_word_for_length_count = 0, no_word_for_letters = 0, have_words_for_length_count = 0, in_the_array_words = 0 , words_not_in_array = 0;

        for(int y = 0; y < word_array_size; y++){

            if(used_word_bool[y] == 0){

                printf("x -%d, y = %d, word = %s\n", x, y, word_list[y]);

                words_tested++;

                if(strlen(word_list[y]) == combined_array[x].length){

                    have_words_for_length_count++; // to compare with words that have filled some letters.
                    int word_filled_ind = 0; // To loop through all the element in the word_filled array.

                    for(int w = 0; w < combined_array[x].word_fill_count; w++){ // check till end of all filled words in the words filled array of the space.

                        if(strcmp(word_list[y], combined_array[x].words_filled[w]) != 0){

                            word_filled_ind++;
                        }
                    }

                    if(word_filled_ind == combined_array[x].word_fill_count){

                        words_not_in_array++;
                        printf("not in array %s, %d\n",word_list[y],x);

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

                                for(int i = 0; i < combined_array[x].length; i++){

                                    if(puzzle_array[combined_array[x].row][combined_array[x].colo + i] == '#'){

                                        puzzle_array[combined_array[x].row][combined_array[x].colo + i] = word_list[y][i];
                                        printf("horizontal element: %c\n",puzzle_array[combined_array[x].row][combined_array[x].colo + i]);

                                        // filled index counting for each space.
                                        combined_array[x].index_x[combined_array[x].filled_index_index] = combined_array[x].row;
                                        combined_array[x].index_y[combined_array[x].filled_index_index] = combined_array[x].colo + i;


                                        printf("The index elements for %d th space: %d, %d\n", x, combined_array[x].index_x[combined_array[x].filled_index_index],combined_array[x].index_y[combined_array[x].filled_index_index]);

                                        combined_array[x].filled_index_index++;

                                    }
                                }

                                strcpy(combined_array[x].words_filled[combined_array[x].word_fill_count], word_list[y]);
                                printf("word filled in space arrray - %s\n", combined_array[x].words_filled[combined_array[x].word_fill_count]);
                                printf("%d %d\n", combined_array[x].word_fill_count, x);

                                used_word_bool[y] = 1;
                                combined_array[x].word_fill_count++;
                                break;

                            }else{ // the word cannot satisfy letters for already filled ones.

                                no_word_for_letters++; // better to check another word from the list.
                                printf("cannot satify filled ones - h \n");
                            }
                        }

                        if(combined_array[x].direction == 'v'){// fill vertically.

                            int non_hash_count = 0;
                            int letter_count = 0;

                            for(int z = 0; z < combined_array[x].length; z++){ // check each index in space

                                if(puzzle_array[combined_array[x].row + z][combined_array[x].colo] != '#'){ // check each index in space non hashes.

                                    non_hash_count++;

                                    if(puzzle_array[combined_array[x].row + z ][combined_array[x].colo] == word_list[y][z]){ // compare the non hash index with word indexes.

                                        letter_count++;
                                    }
                                }
                            }

                            if(letter_count == non_hash_count){ //   This means every non hash index have similar letters.

                                for(int i = 0; i < combined_array[x].length; i++){

                                    if(puzzle_array[combined_array[x].row + i][combined_array[x].colo] == '#'){ // We don't fill once we fill the letter.

                                        puzzle_array[combined_array[x].row + i][combined_array[x].colo] = word_list[y][i];
                                        printf("element: %c\n",puzzle_array[combined_array[x].row + i][combined_array[x].colo]);

                                        // filled index counting for each space.
                                        combined_array[x].index_x[combined_array[x].filled_index_index] = combined_array[x].row +i;
                                        combined_array[x].index_y[combined_array[x].filled_index_index] = combined_array[x].colo;

                                        combined_array[x].filled_index_index++;

                                    }
                                }

                                strcpy(combined_array[x].words_filled[combined_array[x].word_fill_count], word_list[y]);
                                printf("word filled in space arrray - %s\n", combined_array[x].words_filled[combined_array[x].word_fill_count]);

                                used_word_bool[y] = 1;
                                combined_array[x].word_fill_count++;
                                break;

                            }else{ //  word cannot satisfy letters for already filled ones.

                                no_word_for_letters++; // better to check another word from list.
                                printf("cannot satisfy filled ones.- v\n");

                            }
                        } // end of checking vertical

                    }else{ // word is in the space array, try for another.

                        in_the_array_words ++;
                        printf("Word is in the space array.\n");

                    }

                }else{ //  word is not in required length.

                        no_word_for_length_count++;

                        printf("word length is not matching.\n");
                }
            }
        }

        if(no_word_for_length_count == words_tested){// have to go back

            printf("no word for length\n");

            //to make the space filled array empty for combined array[x]

            int should_check = x -1;

            // make the word filled array of combined array[x] empty.
            for(int word_filled_index = combined_array[x].word_fill_count - 1 ; word_filled_index > -1; word_filled_index--){

                strcpy(combined_array[x].words_filled[word_filled_index],combined_array[x].words_filled[word_filled_index + 1]);

            }

            combined_array[x].word_fill_count = 0;

            //Find the word filled in combined array[x-1]
            char last_word[20];
            strcpy(last_word,combined_array[should_check].words_filled[combined_array[should_check].word_fill_count - 1]);

            //Make the last used word in combined array[x-1] available in the word list.

            for(int word_list_index = 0; word_list_index < word_array_size; word_list_index++){

                    if(strcmp(word_list[word_list_index],last_word) == 0){

                        used_word_bool[word_list_index] = 0;
                    }
                }

            //Make the all the indexes filled in combined array[x-1] = #
            for(int index_array_index = 0 ;  index_array_index < combined_array[should_check].filled_index_index ; index_array_index++){

                puzzle_array[combined_array[should_check].index_x[index_array_index]][combined_array[should_check].index_y[index_array_index]] = '#';
            }

            combined_array[should_check].filled_index_index = 0;

            x = should_check - 1;

            continue;

        }else if(have_words_for_length_count == in_the_array_words){ //have to go back, no word can be fount such that not in the array.

            printf("all possible words are tried. go back cuddah.\n");

            //to make the space filled array empty for combined_array[x]

            int should_check = x -1;

            // make the word filled array of combined array[x] empty.
            for(int word_filled_index = combined_array[x].word_fill_count - 1 ; word_filled_index > -1; word_filled_index--){

                strcpy(combined_array[x].words_filled[word_filled_index],combined_array[x].words_filled[word_filled_index + 1]);

            }

            combined_array[x].word_fill_count = 0;

            //Find the word filled in combined array[x-1]
            char last_word[20];
            strcpy(last_word,combined_array[should_check].words_filled[combined_array[should_check].word_fill_count - 1]);

            //Make the last used word in combined array[x-1] available in the word list.

            for(int word_list_index = 0; word_list_index < word_array_size; word_list_index++){

                    if(strcmp(word_list[word_list_index],last_word) == 0){

                        used_word_bool[word_list_index] = 0;
                    }
            }

            //Make the all the indexes filled in combined array[x-1] = #
            for(int index_array_index = 0 ;  index_array_index < combined_array[should_check].filled_index_index ; index_array_index++){

                puzzle_array[combined_array[should_check].index_x[index_array_index]][combined_array[should_check].index_y[index_array_index]] = '#';
            }

            combined_array[should_check].filled_index_index = 0;

            x = should_check - 1;


            continue;

        }else if(words_not_in_array == no_word_for_letters){

            printf("all words not in array are not matching for letters already filled.\n");

            int should_check = x -1;

            // make the word filled array of combined array[x] empty.
            for(int word_filled_index = combined_array[x].word_fill_count - 1 ; word_filled_index > -1; word_filled_index--){

                strcpy(combined_array[x].words_filled[word_filled_index],combined_array[x].words_filled[word_filled_index + 1]);

            }

            combined_array[x].word_fill_count = 0;

            //Find the word filled in combined array[x-1]
            char last_word[20];
            strcpy(last_word,combined_array[should_check].words_filled[combined_array[should_check].word_fill_count - 1]);

            //Make the last used word in combined array[x-1] available in the word list.

            for(int word_list_index = 0; word_list_index < word_array_size; word_list_index++){

                if(strcmp(word_list[word_list_index],last_word) == 0){

                    used_word_bool[word_list_index] = 0;
                }
            }

            //Make the all the indexes filled in combined array[x-1] = #
            for(int index_array_index = 0 ;  index_array_index < combined_array[should_check].filled_index_index ; index_array_index++){

                puzzle_array[combined_array[should_check].index_x[index_array_index]][combined_array[should_check].index_y[index_array_index]] = '#';
            }

            combined_array[should_check].filled_index_index = 0;

            x = should_check - 1;

            continue;
        }
    }

    for(int x = 0; x < puzzle_row; x++){ // printing the array.

        for(int y = 0; y <puzzle_colo; y++){

           printf("%c", puzzle_array[x][y]);
        }

        printf("\n");
    }

    return 0;

}

