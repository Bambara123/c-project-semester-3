if(no_word_for_length_count == words_tested){// have to go back

            printf("no word for length\n");

            //to make the space filled array empty for combined_array[x]

            for(int word_filled_index = combined_array[x].word_fill_count - 1 ; word_filled_index > -1; word_filled_index--){

                    strcpy(combined_array[x].words_filled[word_filled_index],combined_array[x].words_filled[word_filled_index + 1]);

                }

            int combined_array_index = x - 1; // do the same thing for rest. And find last index with problem.

            while(combined_array[combined_array_index].length != combined_array[x].length){

                for(int word_filled_index = combined_array[combined_array_index].word_fill_count ; word_filled_index > -1; word_filled_index--){

                    strcpy(combined_array[combined_array_index].words_filled[word_filled_index],combined_array[combined_array_index].words_filled[word_filled_index+1]);

                }
                combined_array[combined_array_index].word_fill_count = 0; // make it zero for all spaces till the previous one.
                combined_array_index--; // we should go back to combined_array_index.
            }

            char final_word[20]; // this is the final word we assigned to words array in space.

            strcpy(final_word,combined_array[combined_array_index].words_filled[combined_array[combined_array_index].word_fill_count - 1]); // index = word_fill_count - 1

            for(int used_word_list_index = x - 1; used_word_list_index >= combined_array_index; used_word_list_index--){ // make all used word bools 0 till previous point.

                for(int word_list_index = 0; word_list_index < word_array_size; word_list_index++){ // 4 num of words in the list.

                    if(strcmp(word_list[word_list_index], used_words[used_word_list_index]) == 0){

                        used_word_bool[word_list_index] = 0;
                    }
                }

                strcpy(used_words[used_word_list_index], used_words[used_word_list_index + 1]); // make used word list clear up to combined array index.

            }

            int index;
            for(index = filled_index_index - 1; (index_array[index].x != combined_array[combined_array_index].row || index_array[index].y != combined_array[combined_array_index].colo) ; index--){

                if(index_array[index].all_ready_filled == 0){

                    puzzle_array[index_array[index].x][index_array[index].y] = '#';

                }
            }
            if(index_array[index].all_ready_filled == 0){ // this is for first index filled in the space. (The space we searched).
                puzzle_array[index_array[index].x][index_array[index].y] = '#';

            }

            filled_index_index = index; // Index is the index of the letter index array that has been filled. the amount of letters has been filled by then equal to that index.
            x = combined_array_index - 1;

