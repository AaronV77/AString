/**
* @file
* @author Aaron Valoroso <Aaron.A.Valoroso@erdc.dren.mil>
* @date June 15th, 2020
*
* @section Description
*
* This file contains all the library functions for a string implementation in C.
*/
#include "astring.h"

int string_debugger_flag = 0;

//-----------------------------------------------------------------------------------------------------
/**
 * This function will take in a char pointer that will contain a decimal number of various kinds. The
 * goal of this function is to figure out how many digits that are greater than zero after the decimal
 * symbol. 
 *
 * \param[in] incoming_number: is a char pointer containing a decimal number.
 * \param[out] return: will be an integer value of the number of digits greater than zero after the decimal symbol.
 */
int get_number_of_decimal_values(char * incoming_number) {

    // Determine when a decimal is found in the given number.
    int decimal_flag = 0;
    // Keep track of how many numbers (1-9) are after the decimal.
    int number_of_decimal_values = 0;
    // Loop through the given number.
    for (int i = 0; i < strlen(incoming_number); ++i) {
        // Search for the decimal number.
        if (incoming_number[i] == 46)
            decimal_flag = i;
        // If the decimal is found find the last digit between (1-9)
        if (decimal_flag) {
            if (incoming_number[i] >= 49 && incoming_number[i] <= 57)
                number_of_decimal_values = i;
        }
    }
    // If the number of decimal values is that are not zero is negative then set the flag to zero, or to the precise number of decimal values.
    return (number_of_decimal_values - decimal_flag) > 0 ? (number_of_decimal_values - decimal_flag) : 0;
}

//-----------------------------------------------------------------------------------------------------
/**
 * This function will take in a string structure that will realloc the char pointer that is holding the 
 * string. The function will copy the contents of the char pointer in the string structure for safe keeping
 * because realloc cannot be expected to not change the memory / destroy the data inside of the pointer.
 * Once the contents are copied, the char pointer in the structure is re-sized and check for errors. From
 * there the char pointer in the string struct is "cleaned" and then the temporary char pointer contents 
 * are transfered back to the string structure. In the case that the re-size is to make the string smaller,
 * then only the amount of the resize minus one (for null terminator) is copied to the char pointer in 
 * the string structure.
 *
 * \param[in] array: is a string structure.
 * \param[in] new_col_size: is an integer that tells the function how many elements to resize the char pointer too. 
 * \param[out] return (on success): will be an integer value of zero.
 * \param[out] return (on failure): will be an integer value of one.
 */
int column_reallocation(string ** array, int new_col_size) {

	if (string_debugger_flag) printf("Entering the column_reallocation function.\n");

    char * copy = calloc(strlen((*array)->array) + 1, sizeof(char));
    strcpy(copy, (*array)->array);

    (*array)->array = realloc((*array)->array, new_col_size * sizeof(char));
    if (!(char*)(*array)->array) {
        printf("ERROR: There was an issue with the reallocation of your pointer.\n");
        free((char*)(*array)->array);
        return 1;
    }
    memset((*array)->array, 0, new_col_size * sizeof(char));
    strncpy((*array)->array, copy, ((new_col_size - 1) * sizeof(char)));
    free(copy);

	if (string_debugger_flag) printf("Leaving the column_reallocation function.\n");

	return 0;
}

//-----------------------------------------------------------------------------------------------------
/**
 * This function will take two integers that will tell the function how many characters the user wants
 * the string structure char pointer to have and how many characters to increase the char pointer by
 * when space runs out. If either integer is less than zero then a default value of zero is assigned to
 * either of them in the string structure.
 *
 * \param[in] array: is a string structure.
 * \param[in] number_of_columns: is an integer that holds how many elements need to be in the char pointer.
 * \param[in] col_incrementation: is a integer that tells the library how many elements need to be incremented to the pointer when the pointer is filled with data. 
 * \param[out] return (on success): will be a string structure pointer.
 * \param[out] return (on failure): will be a NULL value.
 */
string * salloc(int number_of_columns, int col_incrementation) {

	if (string_debugger_flag) printf("Entering the salloc.\n");

    string * ptr = calloc(1, sizeof(string));

    if (number_of_columns <= 0)
        ptr->total_num_cols = 20;
    else
        ptr->total_num_cols = number_of_columns;

    if (col_incrementation < 0)
        ptr->col_incrementation = 0;
    else 
        ptr->col_incrementation = col_incrementation;

    ptr->array = calloc(ptr->total_num_cols, sizeof(char));
    if (!ptr->array) {
        printf("ERROR: Calloc has failed...\n");
        if (string_debugger_flag) printf("Leaving the salloc function.\n");
        return NULL;
    }

    ptr->tokens = NULL;
    ptr->total_num_tokens = 0;

    if (string_debugger_flag) printf("Leaving the salloc function.\n");
    return ptr;
}

//-----------------------------------------------------------------------------------------------------
/**
 * This function will take a string structure and incoming data to be appened the the char pointer
 * within the string structure. The format for this function can be a mixture of datatypes (char, 
 * string, int, double, float). To have more than one item be appended to the char pointer within 
 * the string structure is by concatenating multiple datatype names together. It has to be all lower
 * case and no characters between each datatype name ("stringcharintdouble"). This is done to make 
 * the function work easier and not have to try and decifer what the user is sending in. A void 
 * pointer is used due to the unknown type of data, and only a char, int, float, double, and char 
 * pointer are accepted. The current length of the char pointer, the incoming length of the data 
 * and null terminator is checked against the amount of memory that is allocated for the char pointer 
 * in the string structure. If there is no room for the incoming data then the function will Take the 
 * combination of lenghts and add the col_incrementation to it, and resize the char pointer in the 
 * string structure. I've debated on keeping the col_incremntation and left it in to allow the user 
 * to control how well this library runs. If the user gives a small to zero number, then the library 
 * will constantly have to keep allocating for more memory to the pointer, else if they give a big 
 * number then less allocates will have to be made (saving some time).
 *
 * \param[in] array: is a string structure.
 * \param[in] format: is a const char pointer that stores the datatype(s) names for the incoming data.
 * \param[in] ...: is either a char or a char pointer of data, nothing else is accpeted.
 * \param[out] return (on success): will be an integer value of zero.
 * \param[out] return (on failure): will be an integer value of one.
 */
int sadd(string ** array, const char * format, ...) {

	if (string_debugger_flag) printf("Entering the sadd function.\n");

    if ((*array)) {
        void * vptr;
        va_list arguments;
        va_start(arguments, format);
        
        string * format_holder = salloc(strlen(format) + 1, 10);
        strcpy(format_holder->array, format);
        format_holder->current_num_col = strlen(format);

        while (1) {
            void * vptr;
            if (!format_holder->current_num_col)
                break;

            if (format_holder->array[0] == 'c') {
                schar_group_delete(&format_holder, 0, 4);
                char * var = calloc(2, sizeof(char));
                var[0] = va_arg(arguments, int);
                vptr = var;
            } else if (format_holder->array[0] == 's') {
                schar_group_delete(&format_holder, 0, 6);
                char * string = va_arg(arguments, char*);
                char * string2 = calloc(strlen(string) + 1, sizeof(char));
                strncpy(string2, string, strlen(string));
                vptr = string2;
            } else if (format_holder->array[0] == 'i') {
                schar_group_delete(&format_holder, 0, 3);
                char  * temp_number = calloc(100, sizeof(char));
                sprintf(temp_number, "%d", va_arg(arguments, int));
                char * actual_number = calloc(strlen(temp_number) + 1, sizeof(char));
                strcpy(actual_number, temp_number);
                free(temp_number);
                vptr = actual_number;
            } else if (format_holder->array[0] == 'd' || format_holder->array[0] == 'f') {
                if (format_holder->array[0] == 'd')
                    schar_group_delete(&format_holder, 0, 6);
                else if (format_holder->array[0] == 'f') 
                    schar_group_delete(&format_holder, 0, 5);

                // Create a temp char pointer for guessing at how big the number is.
                char  * temp_number = calloc(1000, sizeof(char));
                // Save the incoming number as a double.
                double incoming_number = va_arg(arguments, double);
                // Copy the number into a char pointer to figure out the number of decimal positions
                sprintf(temp_number, "%f", incoming_number);
                // Get the number of digits > 0 after the decimal.
                int number_of_decimals = get_number_of_decimal_values(temp_number);
                // Get the base number of digits and decimal into a char array.
                char * actual_number = calloc(strlen(temp_number) + 1, sizeof(char));
                // Copy the number into the previous char array with no tailing zeros.
                sprintf(actual_number, "%.*f", number_of_decimals, incoming_number);
                free(temp_number);
                vptr = actual_number;
            } else {
                printf("ERROR: The given data type is not supported.\n");
                if (string_debugger_flag) printf("Leaving the sadd funtion.\n");
                va_end(arguments);
                if (string_debugger_flag) printf("Leaving the sadd funtion.\n");
                return 1;
            }

            // At this point vptr should all be a char pointer
            int temp_length = (*array)->current_num_col + strlen((char*)vptr) + 1;
            if ((*array)->total_num_cols < temp_length) {
                // Check to see if the added data to the string structure exceeds the current memory buffer.
                // Take the current length and add extra memory for furture adds.
                (*array)->total_num_cols = temp_length + (*array)->col_incrementation;
                // Realloc the char pointer within the string structure for the new lenght.
                column_reallocation(array, (*array)->total_num_cols);
            }
            // Need to subtract one from the temp length due to its addition of the null terminator.
            (*array)->current_num_col = (temp_length - 1);
            // Add the incoming data to the char pointer within the string structure.
            strcat((*array)->array, (char*)vptr);

            free(vptr);
        }

        sfree(&format_holder);

        va_end(arguments);
        if (string_debugger_flag) printf("Leaving the sadd funtion.\n");
        return 0;
    } else
        printf("WARNING: You sent in a NULL pointer...\n");
    
	if (string_debugger_flag) printf("Leaving the sadd funtion.\n");
	return 1;
}

//-----------------------------------------------------------------------------------------------------
/**
 * This function will take a string structure char pointer and insert either a char, int, double, float,
 *  or a char pointer to the char pointer within the string structure. This function was created because 
 * of the sadd function not being able to add characters in the beginning of the string. A void pointer 
 * is used due to the unknown type of data, and only a char or char pointer is accepted. The current length 
 * of the char pointer, the incoming length of the data and null terminator is checked against the amount 
 * of memory that is allocated for the char pointer in the string structure. If there is no room for the 
 * incoming data then the function will Take the combination of lenghts and add the col_incrementation to 
 * it, and resize the char pointer in the string structure. I've debated on keeping the col_incremntation 
 * and left it in to allow the user to control how well this library runs. If the user gives a small to zero
 * number, then the library will constantly have to keep allocating for more memory to the pointer, else if 
 * they give a big number then less allocates will have to be made (saving some time).
 *
 * \param[in] array: is a string structure.
 * \param[in] position: is an integer that tells the function where to insert the incoming data.
 * \param[in] format: is a const char pointer that stores the datatype for the incoming data.
 * \param[in] ...: is either a char or a char pointer of data, nothing else is accpeted.
 * \param[out] return (on success): will be an integer value of zero.
 * \param[out] return (on failure): will be an integer value of one.
 */
int sinsert(string ** array, int position, const char * format, ...) {

	if (string_debugger_flag) printf("Entering the sinsert funtion.\n");

    if ((*array)) {
        void * vptr;
        va_list arguments;
        va_start(arguments, format);

        // Grab the characters that are to be added to the end of a string.
        if (!strcmp(format, "char")) {
            char * var = calloc(2, sizeof(char));
            var[0] = va_arg(arguments, int);
            vptr = var;
        } else if (!strcmp(format, "string")) {
            char * string = va_arg(arguments, char*);
            char * string2 = calloc(strlen(string) + 1, sizeof(char));
            strncpy(string2, string, strlen(string));
            vptr = string2;
        } else if (!strcmp(format, "int")) {
            char  * temp_number = calloc(100, sizeof(char));
            sprintf(temp_number, "%d", va_arg(arguments, int));
            char * actual_number = calloc(strlen(temp_number) + 1, sizeof(char));
            strcpy(actual_number, temp_number);
            free(temp_number);
            vptr = actual_number;
        } else if (!strcmp(format, "float") || !strcmp(format, "double")) {
            // Create a temp char pointer for guessing at how big the number is.
            char  * temp_number = calloc(1000, sizeof(char));
            // Save the incoming number as a double.
            double incoming_number = va_arg(arguments, double);
            // Copy the number into a char pointer to figure out the number of decimal positions
            sprintf(temp_number, "%f", incoming_number);
            // Get the number of digits > 0 after the decimal.
            int number_of_decimals = get_number_of_decimal_values(temp_number);
            // Get the base number of digits and decimal into a char array.
            char * actual_number = calloc(strlen(temp_number) + 1, sizeof(char));
            // Copy the number into the previous char array with no tailing zeros.
            sprintf(actual_number, "%.*f", number_of_decimals, incoming_number);
            free(temp_number);
            vptr = actual_number;
        } else {
            printf("ERROR: The given data type is not supported...\n");
            if (string_debugger_flag) printf("Leaving the sadd funtion.\n");
            va_end(arguments);
            return 1;
        }

        // At this point vptr should all be a char pointer
        int temp_length = (*array)->current_num_col + strlen((char*)vptr) + 1;
        if ((*array)->total_num_cols < temp_length) {
            // Check to see if the added data to the string structure exceeds the current memory buffer.
            // Take the current length and add extra memory for furture adds.
            (*array)->total_num_cols = temp_length + (*array)->col_incrementation;
            // Realloc the char pointer within the string structure for the new lenght.
            column_reallocation(array, (*array)->total_num_cols);
        }
        // Need to subtract one from the temp length due to its addition of the null terminator.
        (*array)->current_num_col = (temp_length - 1);

        // Create a new char pointer to for holding all of the data.
        char * temp = calloc((*array)->current_num_col + 1, sizeof(char));
        // Copy everything up to the point of the position to the new char pointer.
        strncpy(temp, (*array)->array, position * sizeof(char));
        // Add the data that was sent in by the user, again should be a char pointer.
        strcat(temp, (char*)vptr);
        // Copy the rest of the original data from the string structure and add it to the new char pointer.
        strncat(temp, &(*array)->array[position], ((*array)->current_num_col - (position + strlen((char*)vptr))) * sizeof(char));
        // Clear out the original pointer in the string structure.
        memset((*array)->array, 0, (*array)->current_num_col * sizeof(char));
        // Copy the temporary char pointer that is holding all of the data back into the string structure.
        strcpy((*array)->array, temp);

        free(temp);
        free(vptr);
        va_end(arguments);

        if (string_debugger_flag) printf("Leaving the sinsert funtion.\n");
        return 0;
    } else
        printf("WARNING: You sent in a NULL pointer...\n");

    if (string_debugger_flag) printf("Leaving the sinsert funtion.\n");
    return 1;
}

//-----------------------------------------------------------------------------------------------------
/**
 * This function will loop through the char pointer within the string structure and find how many times
 * a character is found within the string. I'm not a big fan of this function because of how simple it
 * is. In the future I wouldn't mind seeing this function also being able to return the position of the
 * first occurence of the char to be found.
 *
 * \param[in] array: is a string structure.
 * \param[in] find_char: is a char that holds a character to be found within a char pointer.
 * \param[out] return (on success): will be an integer of the number of occurences the char has been found in the string.
 */
int soccurences(string * array, char find_char) {

	if (string_debugger_flag) printf("Entering the soccurences function.\n");

    int total_occurences = 0;
    if (array) {
        for (int i = 0; i < array->current_num_col; ++i) {
            if (array->array[i] == find_char)
                total_occurences++;
        }
    } else
        printf("WARNING: You sent in a NULL pointer...\n");

	if (string_debugger_flag) printf("Leaving the soccurences function.\n");
    return total_occurences;
}

//-----------------------------------------------------------------------------------------------------
/**
 * This function will take the string structure char pointer and tokenize it. The tokens are stored in 
 * a two dimensional char array in the string strucutre, as well as how many tokens are found. This
 * function will check to see how many times the tokenizer character can be found in the string and 
 * saved. The returned value will be used to allocate memory to the tokens variable in the string
 * structure. A copy is taken of the char pointer in the string structure due to strtok function being
 * mean and editing the original version. Once a token is found a row in the tokens 2D array is 
 * allocated and the contents of the token are saved to the row. This will loop through all tokens and
 * repeating the same process. The strtok function is not nice with memory or how it interacts with
 * a given char pointer. In the future I want to create my own version of strtok and return the array
 * myself. This function will be updated with said new version of strtok. 
 *
 * \param[in] array: is a string structure.
 * \param[in] token_char: is a char to be used to split the char pointer with.
 * \param[out] return (on success): will be an integer value of zero.
 * \param[out] return (on failure): will be an integer value of one.
 */
int stokenize(string ** array, char token_char) {

	if (string_debugger_flag) printf("Entering the stokenize function.\n");

    if ((*array)) {
        // Note: See how many characters are within the string.
        int character_occurences = soccurences((*array), token_char);
        // Note: If there are occurences of the given character then procced, else leave.
        if (character_occurences) {
            // Note: Check to see if there were tokens already found. 
            if ((*array)->tokens) {
                // Note: Loop through the found tokens for the string and free everything.
                for (int i = 0; i < (*array)->total_num_tokens; ++i)
                    free((*array)->tokens[i]);
                free((*array)->tokens);
                (*array)->tokens = NULL;
                (*array)->total_num_tokens = 0;
            }

            // Note: Have to add another one to the character_occurences because of the extra token at the end.
            (*array)->tokens = calloc(character_occurences + 1, sizeof(char*));
            if (!(*array)->tokens) {
                printf("ERROR: There was an issue with the first calloc call.\n");
                return 1;
            }

            int token_iterator = 0;
            // Note: Temporary token array for storing the given tokens.
            char * token = calloc(256, sizeof(char));

            // Note: Loop through the passed in char array.
            for (int i = 0; i < (*array)->current_num_col; i++) {
                // Note: Check to see if we found a token character or we are at the end of the string.
                if (((*array)->array[i] == token_char) || (i == ((*array)->current_num_col - 1))) {
                    // Note: Check to see if we are at the end of the char array and the token we are adding is not the token character.
                    if (i == (*array)->current_num_col -1 && (*array)->array[i] != token_char) 
                    {
                        // Note: Add the last character to the token from the char array.
                        token[token_iterator] = (*array)->array[i];
                    }

                    // Note: Check to make sure that the token actually has characters in it before adding it.
                    if (strlen(token) > 0)
                    {
                        // Note: Allocate memory for the found token.
                        (*array)->tokens[(*array)->total_num_tokens] = calloc(strlen(token) + 1, sizeof(char));
                        // Note: Check to see if the allocation of memory was successful.
                        if (!(*array)->tokens[(*array)->total_num_tokens]) {
                            printf("ERROR: There was an issue with the second calloc call.\n");
                            if (string_debugger_flag) printf("Leaving the stokenize function.\n");
                            return 1;
                        }

                        // Note: Copy the token string into the array of tokens.
                        strcpy((*array)->tokens[(*array)->total_num_tokens], token);
                        // Note: Increment the number of tokens.
                        (*array)->total_num_tokens++;  
                        // Note; Reset the token string.
                        memset(token, 0, 256 * sizeof(char));    
                        // Note: Reset the iterator used for saving characters into the token array.     
                        token_iterator = 0;
                    }
                } else {
                    // Note: Save the character from the given string into the temporary token string.
                    token[token_iterator] = (*array)->array[i];
                    // Note; Increase the tokens index. 
                    token_iterator++;
                }
            }

            if (string_debugger_flag) printf("Leaving the stokenize function.\n");
            // Note: Cleanup the temp token array.
            free(token);
            
            return 0;
        } 
        else
            printf("WARNING: There were no characters found like that in the following string: %s\n", (*array)->array);
    } 
    else
        printf("WARNING: You sent in a NULL pointer...\n");

	if (string_debugger_flag) printf("Leaving the stokenize function.\n");
    return 1;
}

//-----------------------------------------------------------------------------------------------------
/**
 * This function will take the string structure and do one of two things with the char pointer within 
 * the structure. If the position is given then the function will stick a NULL terminator in the char
 * pointer of the string structure. If the character is given then the function will loop through 
 * the char pointer in the string structure for the first occurence of said character and stick a NULL
 * terminator there.
 *
 * \param[in] array: is a string structure.
 * \param[in] position: is an integer that tells the function where a null terminator needs to be added.
 * \param[in] character: is a char character that tells the function on where a null terminator needs to be added.
 * \param[out] return (on success): will be an integer value of zero and a truncated char pointer.
 * \param[out] return (on failure): will be an integer value of one and a unedited char pointer.
 */
int strunc(string ** array, int position, char character) {

	if (string_debugger_flag) printf("Entering the strunc function.\n");

    if ((*array)) {
        // If the position_or_char is bigger than the length of the string.
        if (character) {
            // Look of the first occurence of a letter and put a null terminator there.
            for (int i = 0; i < (*array)->current_num_col; ++i) {
                if ((*array)->array[i] == character) {
                    (*array)->array[i] = '\0';
                    (*array)->current_num_col = i;

                    if (string_debugger_flag) printf("Leaving the strunc funtion.\n");
                    return 0;
                }
            }
        } else {
            // Put a null terminator at a specific place in the string. 
            (*array)->array[position] = '\0';
            (*array)->current_num_col = position;

            if (string_debugger_flag) printf("Leaving the strunc funtion.\n");
            return 0;            
        }
    } else
        if (string_debugger_flag) printf("WARNING: You sent in a NULL pointer...\n");

	if (string_debugger_flag) printf("Leaving the strunc funtion.\n");
    return 1;
}

//-----------------------------------------------------------------------------------------------------
/**
 * This function will take in a string structure and remove all characters that were passed into this function
 * from the char pointer in the structure. Each characters is checked against the remove characters pointer. All 
 * characters that do not consist of any characters from the remove characters pointer are added to the temporary 
 * pointer. Once finished, the system will clear the string structure, and add the temporary pointer to the string 
 * structure.
 *
 * \param[in] array: is a string structure.
 * \param[in] remove_characters: is a char pointer that holds characters to be removed from said string.
 * \param[out] return (on success): will be an integer value of zero and an updated char pointer.
 * \param[out] return (on failure): will be an integer value of one and the original char pointer. 
 */
int schar_delete(string ** array, char * remove_characters) {

	if (string_debugger_flag) printf("Entering the schar_delete function.\n");

    if ((*array)) {
        int temp_iterator = 0, add_flag = 0, number_of_characters = strlen(remove_characters);
        // Note: Create a temporary pointer that is the same size of the incoming array.
        char * ptr = calloc(((*array)->total_num_cols + 1), sizeof(char));
        // Note: Loop through the incoming array.
        for (int i = 0; i < (*array)->current_num_col; ++i) {
            // Loop though all the characters being removed.
            for (int j = 0; j < number_of_characters; ++j) {
                // Note: Check to see if any of the characters in the array match any of the charcters to be removed.
                if ((*array)->array[i] == remove_characters[j])
                    add_flag = 1;
            }
            
            // Note: Only add charcters to the temporary pointer if they don't match a removed character.
            if (!add_flag)  {
                // Note: Add the character to the temporary pointer.
                ptr[temp_iterator] = (*array)->array[i];
                // Note: Increase the temporary pointer iterator.
                temp_iterator++;
            }
            // Reset the add flag.
            add_flag = 0;
        }
        // Note: Clear the old array out for the new string.
        sclear(array);
        // Add the new array to the old string, this will take care of current_num_col.
        sadd(array, "string", ptr);
        // Note: Free the temporary array.
        free(ptr);

        if (string_debugger_flag) printf("Leaving the schar_delete funtion.\n");
        return 0;
    } else
        printf("WARNING: You sent in a NULL pointer...\n");

	if (string_debugger_flag) printf("Leaving the schar_delete funtion.\n");
    return 1;
}

//-----------------------------------------------------------------------------------------------------
/**
 * This function will take a string structure remove a single character from the given char pointer in the 
 * string structure. The function first checks to make sure that the user is not doing anything silly by 
 * giving a false position. Next, if the user is not doing anything silly, I check to see where the 
 * user is trying to the single character from the char pointer and update a new temporary char 
 * pointer with the data that they want to keep. Once, finished, I reset the char pointer and the number of 
 * characters in the string structure to the update data. Lastly, the starting and ending position are zero
 * based.
 *
 * \param[in] array: is a string structure.
 * \param[in] position: is an integer that tells the function the starting position for removing characters is.
 * \param[out] return (on success): will be an integer value of zero and a string structure with an update char pointer.
 * \param[out] return (on failure): will be an integer value of one and the original data that was sent in.
 */
int schar_single_delete(string ** array, int position) {

	if (string_debugger_flag) printf("Entering the schar_groupd_delete function.\n");

    if ((*array)) 
    {
        // Note: Check to make sure that the starting position is some where within the length of the string structure array.
        if (position > (*array)->current_num_col || position < 0) 
        {
            if (position > (*array)->current_num_col) 
                printf("WARNING: Your starting position is greater than the current length of the string.\n");
            if (position < 0)
                printf("WARNING: Your starting position is less than zero.\n");
            if (string_debugger_flag) printf("Leaving the schar_groupd_delete funtion.\n");
            return 1;
        }

        // Note: Temporary char pointer for storing the new string.
        char * temp = calloc((*array)->current_num_col + 1, sizeof(char));

        // Note: Create a variable for storing the index to the temporary char pointer.
        int counter = 0;
        // Note: Loop through the incoming string array.
        for (int i = 0; i < (*array)->current_num_col; ++i) 
        {
            // Note: If we get to the position for removing a character then skip it.
            if (i == position)
                continue;
            // Note: Save all the wanted characters to the temporary char array.
            temp[counter] = (*array)->array[i];
            // Note: Update the temporary array index. 
            counter++;
        }
        
        // Note: Reset the original char pointer in the string structure.
        memset((*array)->array, 0, (*array)->current_num_col * sizeof(char));
        // Note: Copy the new data into the original char pointer.
        strcpy((*array)->array, temp);
        // Note: Update the number of current characters in the string.
        (*array)->current_num_col -= 1;
        // Note: Cleanup
        free(temp);

        if (string_debugger_flag) printf("Leaving the schar_groupd_delete funtion.\n");
        return 0;
    } 
    else
        printf("WARNING: You sent in a NULL pointer...\n");

	if (string_debugger_flag) printf("Leaving the schar_groupd_delete funtion.\n");
    return 1;
}

//-----------------------------------------------------------------------------------------------------
/**
 * This function will take a string structure remove a group of characters from the given char pointer in the 
 * string structure. The function first checks to make sure that the user is not doing anything silly by 
 * giving a false starting and ending position, and then to see if they are just trying to clear the entire 
 * char pointer in the string structure. Next, if they are not doing anything silly, I check to see where the 
 * user is trying to remove characters from the char pointer and update a new temporary char 
 * pointer with the data that they want to keep. Once, finished, I reset the char pointer and the number of 
 * characters in the string structure to the update data. Lastly, the starting and ending position are zero
 * based.
 *
 * \param[in] array: is a string structure.
 * \param[in] starting_position: is an integer that tells the function the starting position for removing characters is.
 * \param[in] ending_position: is an integer that tells the function the ending position to stop removing characters.
 * \param[out] return (on success): will be an integer value of zero and a string structure with an update char pointer.
 * \param[out] return (on failure): will be an integer value of one and the original data that was sent in.
 */
int schar_group_delete(string ** array, int starting_position, int ending_position) {

	if (string_debugger_flag) printf("Entering the schar_groupd_delete function.\n");

    if ((*array)) {
        if (starting_position > (*array)->current_num_col || starting_position < 0) {
            // Check to make sure that the starting position is some where within the length of the string structure array.
            if (starting_position > (*array)->current_num_col) 
                printf("WARNING: Your starting position is greater than the current length of the string.\n");
            if (starting_position < 0)
                printf("WARNING: Your starting position is less than zero.\n");
            if (string_debugger_flag) printf("Leaving the schar_groupd_delete funtion.\n");
            return 1;
        }

        if (ending_position > (*array)->current_num_col || ending_position < 0) {
            // Check to make sure that the ending position is some where within the length of the string structure array.
            if (ending_position > (*array)->current_num_col) 
                printf("WARNING: Your ending position is greater than the current length of the string.\n");
            if (ending_position < 0)
                printf("WARNING: Your ending position is less than zero.\n");
            if (string_debugger_flag) printf("Leaving the schar_groupd_delete funtion.\n");
            return 1;
        }

        if ((ending_position - starting_position) == (*array)->current_num_col) {
            // Check to see if the user is trying to delete the whole array.
            sclear(array);
            if (string_debugger_flag) printf("Leaving the schar_groupd_delete funtion.\n");
            return 0;
        }

        char * temp = calloc((*array)->current_num_col + 1, sizeof(char));
        if (!starting_position) {
            // Deleting something from the start of the string to the middle.
            strncpy(temp, &(*array)->array[ending_position], ((*array)->current_num_col - ending_position) * sizeof(char));
        } else if (ending_position == (*array)->current_num_col) {
            // Deleting something from the middle of the string to the very end.
            strncpy(temp, (*array)->array, starting_position * sizeof(char));
        } else {
            // Deleting something from the middle of the string to the middle.
            strncpy(temp, (*array)->array, starting_position * sizeof(char));
            strncat(temp, &(*array)->array[ending_position], ((*array)->current_num_col - ending_position) * sizeof(char));
        }
        
        // Reset the original char pointer in the string structure.
        memset((*array)->array, 0, (*array)->current_num_col * sizeof(char));
        // Copy the new data into the original char pointer.
        strcpy((*array)->array, temp);
        // Update the number of current characters in the string.
        (*array)->current_num_col -= (ending_position - starting_position);
        // Cleanup
        free(temp);

        if (string_debugger_flag) printf("Leaving the schar_groupd_delete funtion.\n");
        return 0;
    } else
        printf("WARNING: You sent in a NULL pointer...\n");

	if (string_debugger_flag) printf("Leaving the schar_groupd_delete funtion.\n");
    return 1;
}

//-----------------------------------------------------------------------------------------------------
/**
 * This function will take the string structure and loop through its char pointer ignoring the leading
 * spaces and taking the last account of character in the pointer. This finds where the string actually
 * starts and ends. I grab everything of the string minus leading and trailing spaces, and move the 
 * contents of the string to the front of the pointer. I then adjust the parameters of the string 
 * structure and then NULL terminate the ending porition of the char pointer to remove the trailing spaces.
 *
 * \param[in] array: is a string structure..
 * \param[out] return (on success): will be an integer value of zero and a string structure with an update char pointer.
 * \param[out] return (on failure): will be an integer value of one and the original data that was sent in.
 */
int sremove_leading_and_trailing_spaces(string ** array) {

	if (string_debugger_flag) printf("Entering the sremove_leading_and_trailing_spaces function.\n");

    if ((*array)) {
        int starting_point = 0, ending_point = 0;
        // Note: Loop until we get a valid character for a starting point.
        for (int i = 0; i < (*array)->current_num_col; ++i) {
            // Note: Once we find a character, break from the loop. 
            if (((*array)->array[i] > 32 && (*array)->array[i] < 127))
            {
                starting_point = i;
                break;
            }
        }
        // Note: Loop backwards until we get a valid character for a starting point.
        for (int i = (*array)->current_num_col - 1; i > 0; --i) {
            // Note: Once we find a character, break from the loop. 
            if (((*array)->array[i] > 32 && (*array)->array[i] < 127))
            {
                ending_point = i;
                break;
            }
        }
        
        // Note: I tried the case of just using strncpy to move the content of the string to the beginning of the string but
        // - this causes an issue in valgrind / low level memory. The error is: __strcpy_sse2_unaligned
        char * temp = calloc(((*array)->current_num_col - starting_point) + 1, sizeof(char));
        strncpy(temp, &(*array)->array[starting_point], (*array)->current_num_col - starting_point);
        sclear(array);
        sadd(array, "string", temp);
        free(temp);

        // Note: Determine how many white spaces were removed from the begining of the string.
        ending_point -= starting_point;
        // Note: Subtract the number of spaces were removed from the beginning.
        (*array)->current_num_col -= starting_point;                       
        // Note: Add a null terminator to where the ending point was found on the string.
        (*array)->array[ending_point + 1] = '\0';

        // Note: Have to add a one to the ending point since it is zero based, and have to convert it to one base.
        (*array)->current_num_col -= ((*array)->current_num_col - (ending_point + 1));

        if (string_debugger_flag) printf("Leaving the sremove_leading_and_trailing_spaces funtion.\n");
        return 0;
    } else
        printf("WARNING: You sent in a NULL pointer...\n");

	if (string_debugger_flag) printf("Leaving the sremove_leading_and_trailing_spaces funtion.\n");
    return 1;
}

//-----------------------------------------------------------------------------------------------------
/**
 * This function will take a string structure and clean all the data feilds. If there are any tokens
 * for the current string, then they are free'd and the iterator set to zero. The char pointer is
 * then cleaned and the total number of elements in the array is set to zero.
 *
 * \param[in] array: is a string structure.
 * \param[out] return (on success): will be an integer value of zero and an emptied string structure.
 * \param[out] return (on failure): will be an integer value of one and the original data that was sent in. 
 */
int sclear(string ** array) {
    
    if (string_debugger_flag) printf("Entering the sclear function.\n");

    if ((*array)) {
        if ((*array)->tokens) {
            for (int i = 0; i < (*array)->total_num_tokens; ++i)
                free((*array)->tokens[i]);
            free((*array)->tokens);
            (*array)->tokens = NULL;
            (*array)->total_num_tokens = 0;
        }

        memset((*array)->array, 0, (*array)->total_num_cols * sizeof(char));
        
        (*array)->current_num_col = 0;

        if (string_debugger_flag) printf("Leaving the sclear function.\n");
        return 0; 
    } else
        printf("WARNING: You sent in a NULL pointer...\n");

    if (string_debugger_flag) printf("Leaving the sclear function.\n");
    return 1;
}

//-----------------------------------------------------------------------------------------------------
/**
 * This function will take in a string structure and reset the entire structure. This function will check
 * if either the number of elements for the char pointer or how many has to be increased with every add, has
 * been passed. If so then their fields are updated. If there are tokens for the current string, then they
 * are free'd and the iterator set back to zero. The char pointer is then cleaned and the number of elements
 * iterator is set back to zero.
 *
 * \param[in] array: is a string structure.
 * \param[in] number_of_columns: is an integer that holds how many elements need to be in the char pointer.
 * \param[in] col_incrementation: is a integer that tells the library how many elements need to be incremented to the pointer when the pointer is filled with data. 
 * \param[out] return (on success): will be an integer value of zero and updated string structure.
 * \param[out] return (on failure): will be an integer value of one and the original string structure.
 */
int sreset(string ** array, int number_of_columns, int col_incrementation) {

    if (string_debugger_flag) printf("Entering the sreset function.\n");
    
    if ((*array)) {
        if (col_incrementation)
            (*array)->col_incrementation = col_incrementation;

        if (number_of_columns) {
            (*array)->array = realloc((*array)->array, number_of_columns * sizeof(char));
            if (!(*array)->array) {
                printf("ERROR: There was an issue with reallocating the given pointer.\n");
                if (string_debugger_flag) printf("Leaving the sreset function.\n");
                return 1;
            }
            (*array)->total_num_cols = number_of_columns;
        }
        
        if ((*array)->tokens) {
            for (int i = 0; i < (*array)->total_num_tokens; ++i)
                free((*array)->tokens[i]);
            free((*array)->tokens);
            (*array)->tokens = NULL;
            (*array)->total_num_tokens = 0;
        }

        memset((*array)->array, 0, (*array)->total_num_cols * sizeof(char));
        (*array)->current_num_col = 0;

        if (string_debugger_flag) printf("Leaving the sreset function.\n");
        return 0;
    } else
        printf("WARNING: You sent in a NULL pointer...\n");

    if (string_debugger_flag) printf("Leaving the sreset function.\n");
    return 1;
}

//-----------------------------------------------------------------------------------------------------
/**
 * This function will take in a string structure and free all tokens (if there are any), the char pointer,
 * that holds the string data, and the string structure pointer itself. 
 *
 * \param[in] array: is a string structure.
 * \param[out] return (on success): will be an integer value of zero and updated string structure.
 * \param[out] return (on failure): will be an integer value of one and the original string structure. 
 */
int sfree(string ** array) {

	if (string_debugger_flag) printf("Entering the sfree function.\n");

    if ((*array)) {
        if ((*array)->tokens) {
            for (int i = 0; i < (*array)->total_num_tokens; ++i)
                free((*array)->tokens[i]);
            free((*array)->tokens);
        }

        free((*array)->array);
        free((*array));

        if (string_debugger_flag) printf("Leaving the sfree funtion\n");
        return 0;
    } else
        printf("WARNING: You sent in a NULL pointer...\n");

	if (string_debugger_flag) printf("Leaving the sfree funtion\n");
	return 1;
}