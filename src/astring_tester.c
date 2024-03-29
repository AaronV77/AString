#include "astring.h"

int main() { 
    int test_id = 0;
    string * cstring = salloc(256, 1);

    printf("Welcome to the AString Test Suit\n");
    printf("----------------------------------------------------------\n");
    printf("WARNING-This test is using the function 'sclear' before being tested, watchout for errors.\n");

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

    sclear(&cstring);

    //----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    // Test-2 (sadd)
    test_id = 2;
    printf("Testing sadd...\n");
    sadd(&cstring, "string", "Aaron Valoros");

    if (strcmp(cstring->array, "Aaron Valoros")) {
        printf("Test-%d-1 Failure: The char pointer in the string stucture is %s and should be %s.\n", test_id, cstring->array, "Aaron Valoros");
        return 1;
    }

    if (cstring->current_num_col != strlen("Aaron Valoros")) {
        printf("Test-%d-2 Failure: The current_num_col in the string structure is %d and should be %ld.\n", test_id, cstring->current_num_col, strlen("Aaron Valoros"));
        return 1;
    }

    sadd(&cstring, "char", 'o');
    if (strcmp(cstring->array, "Aaron Valoroso")) {
        printf("Test-%d-3 Failure: The char pointer in the string structure is %s and should be %s.\n", test_id, cstring->array, "Aaron Valoroso");
        return 1;
    }

    if (cstring->current_num_col != strlen("Aaron Valoroso")) {
        printf("Test-%d-4 Failure: The current_num_col in the string structure is %d and should be %ld.\n", test_id, cstring->current_num_col, strlen("Aaron Valoroso"));
        return 1;
    }

    sclear(&cstring);
    sadd(&cstring, "int", 10);
    if (strcmp(cstring->array, "10")) {
        printf("Test-%d-5 Failure: The char pointer in the string structure is %s and should be %s.\n", test_id, cstring->array, "10");
        return 1;
    }

    sclear(&cstring);
    sadd(&cstring, "float", 10.11);
    if (strcmp(cstring->array, "10.11")) {
        printf("Test-%d-6 Failure: The char pointer in the string structure is %s and should be %s.\n", test_id, cstring->array, "10.11");
        return 1;
    }

    sclear(&cstring);
    sadd(&cstring, "double", 10.111234);
    if (strcmp(cstring->array, "10.111234")) {
        printf("Test-%d-7 Failure: The char pointer in the string structure is %s and should be %s.\n", test_id, cstring->array, "10.111234");
        return 1;
    }

    sclear(&cstring);
    sadd(&cstring, "double", 2.000000);
    if (strcmp(cstring->array, "2")) {
        printf("Test-%d-8 Failure: The char pointer in the string structure is %s and should be %s.\n", test_id, cstring->array, "2");
        return 1;
    }

    sclear(&cstring);
    sadd(&cstring, "charstringintdoublefloat", 'A', "Valoroso", 26, 6.4, 230.5);
    if (strcmp(cstring->array, "AValoroso266.4230.5")) {
        printf("Test-%d-9 Failure: The char pointer in the string structure is %s and should be %s.\n", test_id, cstring->array, "AValoroso266.4230.5");
        return 1;
    }

    sclear(&cstring);  

    //----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    // Test-3 (sinsert)
    test_id = 3;
    printf("Testing sinsert...\n");
    sadd(&cstring, "string", "Aaron Valoroso");
    sinsert(&cstring, 6, "string", "Anthony ");

    if (strcmp(cstring->array, "Aaron Anthony Valoroso")) {
        printf("Test-%d-1 Failure: The char pointer in the string structure is %s and should be %s.\n", test_id, cstring->array, "Aaron Valoroso");
        return 1;
    }

    if (cstring->current_num_col != strlen("Aaron Anthony Valoroso")) {
        printf("Test-%d-2 Failure: The current_num_col in the string structure is %d and should be %ld.\n", test_id, cstring->current_num_col, strlen("Aaron Valoroso"));
        return 1;
    }
    
    sinsert(&cstring, 0, "string", "AA");
    if (strcmp(cstring->array, "AAAaron Anthony Valoroso")) {
        printf("Test-%d-3 Failure: The char pointer in the string structure is %s and should be %s.\n", test_id, cstring->array, "AAAaron Anthony Valoroso");
        return 1;
    }

    if (cstring->current_num_col != strlen("AAAaron Anthony Valoroso")) {
        printf("Test-%d-4 Failure: The current_num_col in the string structure is %d and should be %ld.\n", test_id, cstring->current_num_col, strlen("Aaron Anthony Valoroso"));
        return 1;
    }

    sinsert(&cstring, strlen("AAAaron Anthony Valoroso"), "string", "oo");
    if (strcmp(cstring->array, "AAAaron Anthony Valorosooo")) {
        printf("Test-%d-5 Failure: The char pointer in the string structure is %s and should be %s.\n", test_id, cstring->array, "AAAaron Anthony Valorosooo");
        return 1;
    }

    if (cstring->current_num_col != strlen("AAAaron Anthony Valorosooo")) {
        printf("Test-%d-6 Failure: The current_num_col in the string structure is %d and should be %ld.\n", test_id, cstring->current_num_col, strlen("AAAaron Anthony Valorosooo"));
        return 1;
    }

    sinsert(&cstring, 0, "char", 'A');
    if (strcmp(cstring->array, "AAAAaron Anthony Valorosooo")) {
        printf("Test-%d-7 Failure: The char pointer in the string structure is %s and should be %s.\n", test_id, cstring->array, "AAAAaron Anthony Valorosooo");
        return 1;
    }

    if (cstring->current_num_col != strlen("AAAAaron Anthony Valorosooo")) {
        printf("Test-%d-8 Failure: The current_num_col in the string structure is %d and should be %ld.\n", test_id, cstring->current_num_col, strlen("AAAAaron Anthony Valorosooo"));
        return 1;
    }
    
    sinsert(&cstring, strlen("AAAAaron "), "char", 'A');
    if (strcmp(cstring->array, "AAAAaron AAnthony Valorosooo")) {
        printf("Test-%d-9 Failure: The char pointer in the string structure is %s and should be %s.\n", test_id, cstring->array, "AAAAaron AAnthony Valorosooo");
        return 1;
    }

    if (cstring->current_num_col != strlen("AAAAaron AAnthony Valorosooo")) {
        printf("Test-%d-10 Failure: The current_num_col in the string structure is %d and should be %ld.\n", test_id, cstring->current_num_col, strlen("AAAAaron AAnthony Valorosooo"));
        return 1;
    }

    sinsert(&cstring, strlen("AAAAaron AAnthony Valorosooo"), "char", 'o');
    if (strcmp(cstring->array, "AAAAaron AAnthony Valorosoooo")) {
        printf("Test-%d-11 Failure: The char pointer in the string structure is %s and should be %s.\n", test_id, cstring->array, "AAAAaron AAnthony Valorosoooo");
        return 1;
    }

    if (cstring->current_num_col != strlen("AAAAaron AAnthony Valorosoooo")) {
        printf("Test-%d-12 Failure: The current_num_col in the string structure is %d and should be %ld.\n", test_id, cstring->current_num_col, strlen("AAAAaron AAnthony Valorosoooo"));
        return 1;
    }

    sinsert(&cstring, strlen("AAAAaron "), "int", 10);
    if (strcmp(cstring->array, "AAAAaron 10AAnthony Valorosoooo")) {
        printf("Test-%d-13 Failure: The char pointer in the string structure is %s and should be %s.\n", test_id, cstring->array, "AAAAaron 10AAnthony Valorosoooo");
        return 1;
    }

    sinsert(&cstring, strlen("AAAAaron 10AAnthony "), "double", 20.22);
    if (strcmp(cstring->array, "AAAAaron 10AAnthony 20.22Valorosoooo")) {
        printf("Test-%d-14 Failure: The char pointer in the string structure is %s and should be %s.\n", test_id, cstring->array, "AAAAaron 10AAnthony 20.22Valorosoooo");
        return 1;
    }

    sclear(&cstring);    
    
    //----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    // Test-4 (soccurences)
    test_id = 4;
    printf("Testing soccurences...\n");
    sadd(&cstring, "string", "Aaron Valoroso");
    int occurences = soccurences(cstring, ' ');

    if (occurences != 1) {
        printf("Test-%d-1 Failure: The number of occurences in the string structure is %d and should be %d.\n", test_id, occurences, 1);
        return 1;
    }

    sclear(&cstring);

    //----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    // Test-5 (stokenize)
    test_id = 5;
    printf("Testing stokenize...\n");
    sadd(&cstring, "string", " Aaron  Valoroso ");
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

    sclear(&cstring);

    //----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    // Test-6 (schar_group_delete)
    test_id = 6;
    printf("Testing schar_group_delete...\n");
    sadd(&cstring, "string", "Aaron Valoroso");
    schar_group_delete(&cstring, 0, 1);

    if (strcmp(cstring->array, "aron Valoroso")) {
        printf("Test-%d-1 Failure: The char pointer in the string structure is %s and should be %s.\n", test_id, cstring->array, "aron Valoroso");
        return 1;
    }

    schar_group_delete(&cstring, 3, 6);
    if (strcmp(cstring->array, "aroaloroso")) {
        printf("Test-%d-2 Failure: The char pointer in the string structure is %s and should be %s.\n", test_id, cstring->array, "aroaloroso");
        return 1;
    }

    schar_group_delete(&cstring, 6, strlen("aroaloroso"));
    if (strcmp(cstring->array, "aroalo")) {
        printf("Test-%d-3 Failure: The char pointer in the string structure is %s and should be %s.\n", test_id, cstring->array, "aroalo");
        return 1;
    }

    if (cstring->current_num_col != strlen("aroalo")) {
        printf("Test-%d-4 Failure: The current_num_col in the string structure is %d and should be %ld.\n", test_id, cstring->current_num_col, strlen("aroalo"));
        return 1;
    }

    schar_group_delete(&cstring, 0, strlen("aroalo"));
    if (strlen(cstring->array)) {
        printf("Test-%d-5 Failure: The char pointer in the string structure is %s and should empty.\n", test_id, cstring->array);
        return 1;
    }

    sclear(&cstring);
    
    //----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    // Test-7 (schar_detele)
    test_id = 7;
    printf("Testing schar_delete...\n");
    sadd(&cstring, "string", "Aar");
    schar_delete(&cstring, "Aa");

    if (strcmp(cstring->array, "r")) {
        printf("Test-%d-1 Failure: The char pointer in the string structure is %s and should be %s.\n", test_id, cstring->array, "r");
        return 1;
    }

    if (cstring->current_num_col != 1) {
        printf("Test-%d-2 Failure: The current_num_col in the string structure is %d and should be %d.\n", test_id, cstring->current_num_col, 1);
        return 1;
    }

    sclear(&cstring);

    //----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    // Test-8 (strunc)
    test_id = 8;
    printf("Testing strunc...\n");
    sadd(&cstring, "string", "Aaron Valoroso");
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

    sclear(&cstring);

    //----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    // Test-9 (sclear)
    test_id = 9;
    printf("Testing sclear...\n");
    sadd(&cstring, "string", "Aaron Valoroso");
    sclear(&cstring);

    if (strlen(cstring->array) != 0) {
        printf("Test-%d-1 Failure: The char pointer in the string structure is %ld and should be %d.\n", test_id, strlen(cstring->array), 0);
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

    sclear(&cstring);

    //----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    // Test-10 (sremove_leading_and_trailing_spaces)
    test_id = 10;
    printf("Testing sremove_leading_and_trailing_spaces...\n");
    sadd(&cstring, "string", "    Aaron Valoroso    ");
    sremove_leading_and_trailing_spaces(&cstring);

    if (strcmp(cstring->array, "Aaron Valoroso")) {
        printf("Test-%d-1 Failure: The char pointer in the string structure is %s and should be %s.\n", test_id, cstring->array, "Aaron Valoroso");
        return 1;
    }

    if (cstring->current_num_col != strlen("Aaron Valoroso")) {
        printf("Test-%d-2 Failure: The current_num_col in the string structure is %d and should be %ld.\n", test_id, cstring->current_num_col, strlen("Aaron Valoroso"));
        return 1;
    }

    sremove_leading_and_trailing_spaces(&cstring);
    if (strcmp(cstring->array, "Aaron Valoroso")) {
        printf("Test-%d-3 Failure: The char pointer in the string structure is %s and should be %s.\n", test_id, cstring->array, "Aaron Valoroso");
        return 1;
    }

    if (cstring->current_num_col != strlen("Aaron Valoroso")) {
        printf("Test-%d-4 Failure: The current_num_col in the string structure is %d and should be %ld.\n", test_id, cstring->current_num_col, strlen("Aaron Valoroso"));
        return 1;
    }

    sclear(&cstring);

    //----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    // Test-11 (schar-single-delete)
    test_id = 11;
    printf("Testing schar-single-delete...\n");
    sadd(&cstring, "string", "Valoroso");
    schar_single_delete(&cstring, 0);

    if (strcmp(cstring->array, "aloroso")) {
        printf("Test-%d-1 Failure: The char pointer in the string structure is %s and should be %s.\n", test_id, cstring->array, "aloroso");
        return 1;
    }

    if (cstring->current_num_col != strlen("aloroso")) {
        printf("Test-%d-2 Failure: The current_num_col in the string structure is %d and should be %ld.\n", test_id, cstring->current_num_col, strlen("aloroso"));
        return 1;
    }

    schar_single_delete(&cstring, 1);

    if (strcmp(cstring->array, "aoroso")) {
        printf("Test-%d-1 Failure: The char pointer in the string structure is %s and should be %s.\n", test_id, cstring->array, "aoroso");
        return 1;
    }

    if (cstring->current_num_col != strlen("aoroso")) {
        printf("Test-%d-2 Failure: The current_num_col in the string structure is %d and should be %ld.\n", test_id, cstring->current_num_col, strlen("aoroso"));
        return 1;
    }

    schar_single_delete(&cstring, cstring->current_num_col - 1);

    if (strcmp(cstring->array, "aoros")) {
        printf("Test-%d-1 Failure: The char pointer in the string structure is %s and should be %s.\n", test_id, cstring->array, "aoros");
        return 1;
    }

    if (cstring->current_num_col != strlen("aoros")) {
        printf("Test-%d-2 Failure: The current_num_col in the string structure is %d and should be %ld.\n", test_id, cstring->current_num_col, strlen("aoros"));
        return 1;
    }

    sclear(&cstring);

    //----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    // Test-12 (sreset)
    test_id = 12;
    printf("Testing sreset...\n");
    sadd(&cstring, "string", "Aaron Valoroso");
    stokenize(&cstring, ' ');

    sreset(&cstring, 120, 10);

    if (strlen(cstring->array) != 0) {
        printf("Test-%d-1 Failure: The char pointer in the string structure is %ld and should be %d.\n", test_id, strlen(cstring->array), 0);
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

    printf("----------------------------------------------------------\n");
    printf("All tests passed inspection!\n");
    return 0;
}