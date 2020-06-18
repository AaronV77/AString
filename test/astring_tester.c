#include "astring.h"

int main() { 
    int test_id = 0;
    string * cstring;
    salloc(&cstring, 256, 1);

    // Test-1 (salloc)
    test_id = 1;
    printf("Testing salloc...\n");

    if (cstring->col_incrementation != 1) {
        printf("Test-%d-1 Failure: The string structure col_incrementation is %d and should be %d.\n", test_id, cstring->col_incrementation, 1);
        return 1;
    }

    if (cstring->total_num_cols != 256) {
        printf("Test-%d-2 Failure: The string structure total_num_cols is %d and should be %d.\n", test_id, cstring->total_num_cols, 256);
        return 1;
    }

    // Test-2 (sadd)
    test_id = 2;
    printf("Testing sadd...\n");
    sadd(&cstring, "string", "Aaron Valoros");

    if (strcmp(cstring->array, "Aaron Valoros")) {
        printf("Test-%d-1 Failure: The char pointer in the string stucture is %s and should be %s.\n", test_id, cstring->array, "Aaron Valoros");
        return 1;
    }

    if (cstring->current_num_col != strlen("Aaron Valoros")) {
        printf("Test-%d-2 Failure: The current_num_col in the string structure is %d and should be %d.\n", test_id, cstring->current_num_col, strlen("Aaron Valoros"));
        return 1;
    }

    sadd(&cstring, "char", 'o');
    if (strcmp(cstring->array, "Aaron Valoroso")) {
        printf("Test-%d-3 Failure: The char pointer in the string structure is %s and should be %s.\n", test_id, cstring->array, "Aaron Valoroso");
        return 1;
    }

    if (cstring->current_num_col != strlen("Aaron Valoroso")) {
        printf("Test-%d-4 Failure: The current_num_col in the string structure is %d and should be %d.\n", test_id, cstring->current_num_col, strlen("Aaron Valoroso"));
        return 1;
    }

    // Test-3 (soccurences)
    test_id = 3;
    printf("Testing soccurences...\n");
    int occurences = soccurences(cstring, ' ');

    if (occurences != 1) {
        printf("Test-%d-1 Failure: The number of occurences in the string structure is %d and should be %d.\n", test_id, occurences, 1);
        return 1;
    }

    // Test-4 (stokenize)
    test_id = 4;
    printf("Testing stokenize...\n");
    stokenize(&cstring, ' ');

    if (cstring->total_num_tokens != 2) {
        printf("Test-%d-1 Failure: The total_num_tokens in the string structure is %d and should be %d.\n", test_id, cstring->total_num_tokens, 2);
        return 1;
    }

    if (strcmp(cstring->tokens[0], "Aaron")) {
        printf("Test-%d-2 Failure: The first token in the string structure tokens is %s and should be %s.\n", test_id, cstring->tokens[0], "Aaron");
        return 1;
    }

    if (strcmp(cstring->tokens[1], "Valoroso")) {
        printf("Test-%d-3 Failure: The second token in the string structure tokens is %s and should be %s.\n", test_id, cstring->tokens[1], "Valoroso");
        return 1;
    }
    
    // Test-5 (strunc)
    test_id = 5;
    printf("Testing strunc...\n");
    strunc(&cstring, 0, ' ');

    if (strcmp(cstring->array, "Aaron")) {
        printf("Test-%d-1 Failure: The char pointer in the string structure is %s and should be %s.\n", test_id, cstring->array, "Aaron");
        return 1;
    }

    if (cstring->current_num_col != 5) {
        printf("Test-%d-2 Failure: The current_num_col in the string structure is %d and should be %d.\n", test_id, cstring->current_num_col, 5);
        return 1;
    }

    strunc(&cstring, 3, 0);
    if (strcmp(cstring->array, "Aar")) {
        printf("Test-%d-3 Failure: The char pointer in the string structure is %s and should be %s.\n", test_id, cstring->array, "Aar");
        return 1;
    }

    if (cstring->current_num_col != 3) {
        printf("Test-%d-2 Failure: The current_num_col in the string structure is %d and should be %d.\n", test_id, cstring->current_num_col, 3);
        return 1;
    }

    // Test-6 (sremove)
    test_id = 6;
    printf("Testing sremove...\n");
    sremove(&cstring, "Aa");

    if (strcmp(cstring->array, "r")) {
        printf("Test-%d-1 Failure: The char pointer in the string structure is %s and should be %s.\n", test_id, cstring->array, "r");
        return 1;
    }

    if (cstring->current_num_col != 1) {
        printf("Test-%d-2 Failure: The current_num_col in the string structure is %d and should be %d.\n", test_id, cstring->current_num_col, 1);
        return 1;
    }

    // Test-7 (sclear)
    test_id = 7;
    printf("Testing sclear...\n");
    sclear(&cstring);

    if (strlen(cstring->array) != 0) {
        printf("Test-%d-1 Failure: The char pointer in the string structure is %d and should be %d.\n", test_id, strlen(cstring->array), 0);
        return 1;
    }

    if (cstring->current_num_col != 0) {
        printf("Test-%d-2 Failure: The current_num_col in the string structure is %d and should be %d.\n", test_id, cstring->current_num_col, 0);
        return 1;
    }

    if (cstring->tokens) {
        printf("Test-%d-3 Failure: The tokens double pointer in the string structure should be empty and its not.\n", test_id);
        return 1;
    }

    if (cstring->total_num_tokens != 0) {
        printf("Test-%d-4 Failure: The total_num_tokens in the string structure is %d and should be %d.\n", test_id, cstring->total_num_tokens, 0);
        return 0;
    }

    // Test-8 (sremove_leading_and_trailing_spaces)
    test_id = 8;
    printf("Testing sremove_leading_and_trailing_spaces...\n");
    sadd(&cstring, "string", "    Aaron Valoroso    ");
    sremove_leading_and_trailing_spaces(&cstring);

    if (strcmp(cstring->array, "Aaron Valoroso")) {
        printf("Test-%d-1 Failure: The char pointer in the string structure is %s and should be %s.\n", test_id, cstring->array, "Aaron Valoroso");
        return 1;
    }

    if (cstring->current_num_col != strlen("Aaron Valoroso")) {
        printf("Test-%d-2 Failure: The current_num_col in the string structure is %d and should be %d.\n", test_id, cstring->current_num_col, strlen("Aaron Valoroso"));
        return 1;
    }
    // This is for the next test.
    stokenize(&cstring, ' ');

    // Test-9 (sreset)
    test_id = 9;
    printf("Testing sreset...\n");
    sreset(&cstring, 120, 10);

    if (strlen(cstring->array) != 0) {
        printf("Test-%d-1 Failure: The char pointer in the string structure is %d and should be %d.\n", test_id, strlen(cstring->array), 0);
        return 1;
    }

    if (cstring->current_num_col != 0) {
        printf("Test-%d-2 Failure: The current_num_col in the string structure is %d and should be %d.\n", test_id, cstring->current_num_col, 0);
        return 1;
    }

    if (cstring->total_num_cols != 120) {
        printf("Test-%d-3 Failure: The total_num_cols in the string structure is %d and should be %d.\n", test_id, cstring->total_num_cols, 120);
        return 1;
    }

    if (cstring->col_incrementation != 10) {
        printf("Test-%d-4 Failure: The col_incrementation in the string structure is %d and should be %d.\n", test_id, cstring->col_incrementation, 10);
        return 1;
    }

    if (cstring->tokens) {
        printf("Test-%d-5 Failure: The tokens double pointer in the string structure should be empty and its not.\n", test_id);
        return 1;
    }

    if (cstring->total_num_tokens != 0) {
        printf("Test-%d-6 Failure: The total_num_tokens in the string structure is %d and should be %d.\n", test_id, cstring->total_num_tokens, 0);
        return 0;
    }

    printf("To test the sfree function then make sure to use valgrind.\n");
    sfree(&cstring);

    return 0;
}