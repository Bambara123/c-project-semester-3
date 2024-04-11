#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int No_of_Columns(char **s); // fuction for getting number of column of grid.
int check_grid(char **puzzle_array); // check for invalid input.

int word_array_size = 0;
int puzzle_row;
int puzzle_colo;

typedef struct _ {

    int row;
    int colo;
    int length;
    int word_fill_count;
    char direction; // 'v' - vertical, 'h' - horizontal
    char words_filled[30][20];  

    int index_x[100]; // for getting filled indexes for an array.
    int index_y[100]; // for getting filled indexes for an array.
    int filled_index_index;  // no of indexes added.

} word_space;

int main(){

    word_space *array = malloc(sizeof(word_space)*100);
    word_space *array_v = malloc(sizeof(word_space) * 100);
    word_space *combined_array = malloc(sizeof(word_space)* 100);
    int *used_word_bool = (int*)calloc(100, sizeof(int)); 

    char **puzzle_array = malloc(sizeof(char *) * 100); // To get the puzzle.
    char **word_list = malloc(sizeof(char *) * 100);  // To get the words.
    char temp;
    int *impossible = (int*)malloc(sizeof(int));
    *impossible = 0;

    puzzle_array[puzzle_row] = malloc(sizeof(char *) * 20); // Just declare the first space for puzzle. 

    while(scanf("%[^\n]%*c",puzzle_array[puzzle_row])==1){ // Take puzzle input.
        puzzle_row++;
        puzzle_array[puzzle_row] = malloc(sizeof(char *) * 20);
    }
    scanf("%c",&temp); //variable to capture the newline

    word_list[word_array_size] = malloc(sizeof(char)*20); // Just declare the first space for word_list. 

    while(scanf("%[^\n]%*c",word_list[word_array_size])==1){ // Take words inputs.
        word_array_size++;
        word_list[word_array_size] = malloc(sizeof(char)*20); // Declare one more space for word_array.
    }

    puzzle_colo = No_of_Columns(puzzle_array);

    int tempc=check_grid(puzzle_array); // Check grid for invalid inputs
    if(tempc==1){
        printf("INVALID INPUT\n");
        return 0;
    }
// --------------------------------------------------------------
    int *word_space_array_count = (int*)malloc(sizeof(int*));
    *word_space_array_count = 0; // Find  horizontal spaces.

    for(int x = 0; x < puzzle_row; x++){

        int *word_length = (int*)malloc(sizeof(int));
        *word_length = 0;
        int *start_row = (int*)malloc(sizeof(int));
        *start_row = 0;
        int *start_colo = (int*)malloc(sizeof(int));
        *start_colo = 0;
        int *counting_started = (int*)malloc(sizeof(int));
        *counting_started = 0;
        int *counting_enabled = (int*)malloc(sizeof(int));
        *counting_enabled = 0;

        for(int y = 0; y < puzzle_colo; y ++){

            if(puzzle_array[x][y] != '*' && *counting_started == 0){ // finding first #.
                (*word_length)++;
                *counting_started = 1;
                *counting_enabled = 1;
                *start_row = x;
                *start_colo = y;

            }else if(puzzle_array[x][y] != '*' && *counting_enabled == 1){ // What happens after found first # or a letter and start counting spaces.
                (*word_length)++;

            }else if(puzzle_array[x][y]== '*'){ // what happens when * is there
                *counting_started = 0;
                *counting_enabled = 0;

                if(*word_length > 1){ // If * is encountered, check for a word space.

                    array[*word_space_array_count].row = *start_row;
                    array[*word_space_array_count].colo = *start_colo;
                    array[*word_space_array_count].length = *word_length;
                    array[*word_space_array_count].direction = 'h';

                    (*word_space_array_count)++;
                }
                *word_length = 0;

            }
        }

        if(*word_length > 1){ //  At the end of the row, check for a word space.

            array[*word_space_array_count].row = *start_row;
            array[*word_space_array_count].colo = *start_colo;
            array[*word_space_array_count].length = *word_length;
            array[*word_space_array_count].direction = 'h';

            (*word_space_array_count)++;
        }
    }

// -------------------------------------------------------------------------------------------------------------------- 
    // Find  vertical spaces.

    int *word_space_array_count_v = (int*)malloc(sizeof(int)); 
    *word_space_array_count_v = 0; 

    for(int x = 0; x < puzzle_colo; x++){
        
        int *word_length_v = (int*)malloc(sizeof(int));
        *word_length_v = 0;
        int *start_row_v = (int*)malloc(sizeof(int));
        *start_row_v = 0;
        int *start_colo_v = (int*)malloc(sizeof(int));
        *start_colo_v = 0;
        int *counting_started_v = (int*)malloc(sizeof(int));
        *counting_started_v = 0;
        int *counting_enabled_v = (int*)malloc(sizeof(int));
        *counting_enabled_v = 0;
        

        for(int y = 0; y < puzzle_row; y ++){

            if(puzzle_array[y][x] != '*' && *counting_started_v == 0){ // What happens after found first # or a letter and start counting spaces.
                *word_length_v = *word_length_v +1;
                *counting_started_v = 1;
                *counting_enabled_v = 1;
                *start_row_v = y;
                *start_colo_v = x;

            }else if(puzzle_array[y][x] != '*' && *counting_enabled_v == 1){
                *word_length_v = *word_length_v +1;

            }else if(puzzle_array[y][x]== '*'){ // what happens when * is there
                *counting_started_v = 0;
                *counting_enabled_v = 0;

                if(*word_length_v > 1){  // If * is encountered, check for a word space.

                    array_v[*word_space_array_count_v].row = *start_row_v;
                    array_v[*word_space_array_count_v].colo = *start_colo_v;
                    array_v[*word_space_array_count_v].length = *word_length_v;
                    array_v[*word_space_array_count_v].direction = 'v';

                    (*word_space_array_count_v)++;

                }

                *word_length_v = 0;
            }
        }

        if(*word_length_v > 1){   //At the end of the column, check for a word space.

            array_v[*word_space_array_count_v].row = *start_row_v;
            array_v[*word_space_array_count_v].colo = *start_colo_v;
            array_v[*word_space_array_count_v].length = *word_length_v;
            array_v[*word_space_array_count_v].direction = 'v';

            (*word_space_array_count_v)++;
        }

        free(word_length_v);
    }

    int c_a_count = 0; // combine horizontal and vertical arrays.

    for(int x = 0; x < *word_space_array_count; x++){

        combined_array[x] = array[x];
        c_a_count++;
    }

    for (int x = 0; x < *word_space_array_count_v; x++){

        combined_array[c_a_count + x] = array_v[x];

    }

    c_a_count = *word_space_array_count + *word_space_array_count_v; // number of elements in combined array

    free(word_space_array_count); // Free this
    free(word_space_array_count_v);

// -------------------------------------------------------------------------------------------------------------------------------
    // Filling grid.
    for(int x = 0; x < c_a_count; x++){

        int words_tested = 0, no_word_for_length_count = 0, no_word_for_letters = 0, have_words_for_length_count = 0, in_the_array_words = 0 , words_not_in_array = 0;

        for(int y = 0; y < word_array_size; y++){

            if(used_word_bool[y] == 0){  // check whether word is already used or not.

                words_tested++;

                if(strlen(word_list[y]) == combined_array[x].length){  // Compare the length of word and the space to be filled.

                    have_words_for_length_count++; // to compare with words that have filled some letters.
                    int word_filled_ind = 0; // To loop through all the element in the word_filled array.

                    for(int w = 0; w < combined_array[x].word_fill_count; w++){ // check till end of all filled words in the words filled array of the space.

                        if(strcmp(word_list[y], combined_array[x].words_filled[w]) != 0){

                            word_filled_ind++;
                        }
                    }

                    if(word_filled_ind == combined_array[x].word_fill_count){ // If the selected word is not in the word filled array we can go next space.

                        words_not_in_array++;

                        if(combined_array[x].direction == 'h'){  // fill horizontally.

                            int non_hash_count = 0;
                            int letter_count = 0;

                            for(int z = 0; z < combined_array[x].length; z++){

                                if(puzzle_array[combined_array[x].row][combined_array[x].colo + z] != '#'){ // Check the already filled letters in given space.

                                    non_hash_count++;

                                    if(puzzle_array[combined_array[x].row][combined_array[x].colo + z] == word_list[y][z]){ // Check the compatibility of the selected word for already filled spaces.

                                        letter_count++;
                                    }
                                }
                            }

                            if(letter_count == non_hash_count){  // This executes, if selected word is compatible with all the letters already filled.

                                for(int i = 0; i < combined_array[x].length; i++){

                                    if(puzzle_array[combined_array[x].row][combined_array[x].colo + i] == '#'){

                                        puzzle_array[combined_array[x].row][combined_array[x].colo + i] = word_list[y][i];

                                        // filled index counting for each space.
                                        combined_array[x].index_x[combined_array[x].filled_index_index] = combined_array[x].row;
                                        combined_array[x].index_y[combined_array[x].filled_index_index] = combined_array[x].colo + i;
                                        combined_array[x].filled_index_index++;
                                    }
                                }

                                strcpy(combined_array[x].words_filled[combined_array[x].word_fill_count], word_list[y]);

                                used_word_bool[y] = 1;
                                combined_array[x].word_fill_count++;
                                break;

                            }else{ // the word cannot satisfy letters for already filled ones.

                                no_word_for_letters++; // better to check another word from the list.

                            }
                        }

                        if(combined_array[x].direction == 'v'){// fill vertically.

                            int non_hash_count = 0;
                            int letter_count = 0;

                            for(int z = 0; z < combined_array[x].length; z++){ // check each index in space

                                if(puzzle_array[combined_array[x].row + z][combined_array[x].colo] != '#'){ // Check the already filled letters in given space.

                                    non_hash_count++;

                                    if(puzzle_array[combined_array[x].row + z ][combined_array[x].colo] == word_list[y][z]){ // Check the compatibility of the selected word for already filled spaces.

                                        letter_count++;
                                    }
                                }
                            }

                            if(letter_count == non_hash_count){ // This executes, if selected word is compatible with all the letters already filled.

                                for(int i = 0; i < combined_array[x].length; i++){

                                    if(puzzle_array[combined_array[x].row + i][combined_array[x].colo] == '#'){ // We don't fill once we fill the letter.

                                        puzzle_array[combined_array[x].row + i][combined_array[x].colo] = word_list[y][i];

                                        // filled index counting for each space.
                                        combined_array[x].index_x[combined_array[x].filled_index_index] = combined_array[x].row +i;
                                        combined_array[x].index_y[combined_array[x].filled_index_index] = combined_array[x].colo;
                                        combined_array[x].filled_index_index++;
                                    }
                                }

                                strcpy(combined_array[x].words_filled[combined_array[x].word_fill_count], word_list[y]);
                                used_word_bool[y] = 1;
                                combined_array[x].word_fill_count++;
                                break;

                            }else{ //  word cannot satisfy letters for already filled ones.

                                no_word_for_letters++; // better to check another word from list.
                            }
                        } 

                    }else{ // Chose word is previously filled for this space and didn't work, so pick a different word from the word_list.

                        in_the_array_words ++;
                    }

                }else{ //  word is not in required length.

                        no_word_for_length_count++;
                }
            }
        }

        if((no_word_for_length_count == words_tested) || (words_not_in_array == no_word_for_letters) || (have_words_for_length_count == in_the_array_words)){// have to go back

            if(x == 0){ //print impossible, if puzzle cannot be solved using given words.

                printf("IMPOSSIBLE");
                *impossible = 1;
                break;
            }

            //to make the space filled array empty for combined array[x]
            int should_check = x -1;

            // make the word filled array of combined array[x] empty.
            for(int word_filled_index = combined_array[x].word_fill_count - 1 ; word_filled_index > -1; word_filled_index--){

                strcpy(combined_array[x].words_filled[word_filled_index],combined_array[x].words_filled[word_filled_index + 1]);

            }
            combined_array[x].word_fill_count = 0;  // When we go back word filled count should be set to 0.

            char last_word[20]; //Find the word filled in combined array[x-1]
            strcpy(last_word,combined_array[should_check].words_filled[combined_array[should_check].word_fill_count - 1]);

            //Make the last used word in combined array[x-1] available in the word list.
            for(int word_list_index = 0; word_list_index < word_array_size; word_list_index++){

                    if(strcmp(word_list[word_list_index],last_word) == 0){

                        used_word_bool[word_list_index] = 0;
                    }
                }

            //Make the all the indexes filled last time  in combined array[x-1] = #
            for(int index_array_index = 0 ;  index_array_index < combined_array[should_check].filled_index_index ; index_array_index++){

                puzzle_array[combined_array[should_check].index_x[index_array_index]][combined_array[should_check].index_y[index_array_index]] = '#';
            }

            combined_array[should_check].filled_index_index = 0;
            x = should_check - 1;
            continue;
        }
    }

    if(*impossible == 0){ //Print the puzzle, if we could find the solution.

        for(int x = 0; x < puzzle_row; x++){ 

            for(int y = 0; y <puzzle_colo; y++){

               printf("%c", puzzle_array[x][y]);
            }
            printf("\n");
        }
    }

    free(impossible); 

    return 0;
}

int No_of_Columns(char **s){    //function to return column number in puzzle grid
    int columns=0;
    for(int i=0;s[0][i]!='\0';i++){
        columns++;
    }
    return columns;
}

int check_grid(char **puzzle_array){   //function to check  wether the given puzzle is valid or not
    int c_=0;
    for(int i=0;i<puzzle_row;i++){
        for(int j=0;j<No_of_Columns(puzzle_array);j++){
            if(puzzle_array[i][j]!='*' && puzzle_array[i][j]!='#' && isalpha(puzzle_array[i][j])==0 ){//check if there is symbole or number in the grid
                c_=1;
                break;
            }
        }
    }
    return c_;  //return 1 if there is a invalid num, return 0 if there are not
}
