#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_ARR_LEN 100000
/*============================================================================
| Assignment: pa01 - Encrypting a plaintext file using the Hill cipher
|
| Author: Adan Rojas
| Language: c, c++, Java, go, python, rust
| To Compile: javac pa01.java
|             gcc -o pa01 pa01.c
|             g++ -o pa01 pa01.cpp
|             go build pa01.go
|             rustc pa01.rs
| To Execute: java -> java pa01 kX.txt pX.txt
|        or   c++ -> ./pa01 kX.txt pX.txt
|        or   c -> ./pa01 kX.txt pX.txt
|        or   go -> ./pa01 kX.txt pX.txt
|        or   rust -> ./pa01 kX.txt pX.txt
|        or   python -> python3 pa01.py kX.txt pX.txt
|                       where kX.txt is the keytext file
|                       and pX.txt is plaintext file
|       Note:
|             All input files are simple 8 bit ASCII input
|             All execute commands above have been tested on Eustis
|
|       Class: CIS3360 - Security in Computing - Fall 2024
| Instructor: McAlpin
|   Due Date: per assignment
+===========================================================================*/

//Prototypes
void FillKeyIn(FILE * key_f, int ** hill_key, int dim);
char *GetOnlyAlpha(char *plain_txt);
char *HillCipher(int ** hill_key, char * plain_txt, int dim, int px_length, int loop1);
void PrintCipherText(char * cipher_txt);
void PrintPlainText(char * only_alpha);

//Fill and print Key Matrix Function
void FillKeyIn(FILE * key_f, int **hill_key, int dim) {
    if (hill_key == NULL) return;

    // Iterate through the Key matrix, get input, print output

    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            fscanf(key_f, "%d", &hill_key[i][j]);
            printf("%4d", hill_key[i][j]);
        }
        printf("\n");
    }
}

// Get Only alpha characters and lowercase them!
char *GetOnlyAlpha(char * plain_txt) {
    char *plain_txt_arr = malloc(sizeof(char) * MAX_ARR_LEN);
    int position = 0;

    for (int len = 0; len < strlen(plain_txt); len++) {
        if (isalpha(plain_txt[len]) && ('A' <= plain_txt[len] && plain_txt[len] <= 'z')) {
            plain_txt_arr[position] = tolower(plain_txt[len]);
            position++;
        }
    }
    plain_txt_arr[position] = '\0';
    return plain_txt_arr;
}

// Alphabet with indexes
char alphabet[26] = {'a', 'b','c','d','e','f','g',
                     'h','i','j','k','l','m','n',
                     'o','p','q','r','s','t','u',
                     'v','w','x','y','z'};

// Make the Hill CIpher encryption function!
char *HillCipher(int ** hill_key, char * plain_txt, int dim, int px_length, int loop1) {

    // Initialize pointer!!! to point at a section of memory to hold the final cipher txt
    char *cipher_txt = malloc(sizeof(char) * MAX_ARR_LEN);
    int p_txt_num[MAX_ARR_LEN] = {0};
    int alpha_index = 0;

    // Convert plain txt with padding to numbers and store
    for (int i = 0; i < strlen(plain_txt); i++) {
        for (int j = 0; j < 26; j++) {
            if (plain_txt[i] == alphabet[j]) {
                p_txt_num[alpha_index] = j;
                break;
            }
        }
        alpha_index++;
    }

    alpha_index = 0;

    // Hill Cipher Calculations, 3 for loops to loop through the cipher blocks
    // Loop through the key col, and row! and perform the encryption!
    for (int walker = 0; walker < loop1; walker++) {
        int index = walker * dim;
        for (int i = 0; i < dim; i++) {
            int cipher_calc = 0;
            for (int j = 0; j < dim; j++) {
                cipher_calc += hill_key[i][j] * p_txt_num[index + j];
            }
            cipher_calc = cipher_calc % 26;
            cipher_txt[alpha_index] = alphabet[cipher_calc];
            alpha_index++;
        }
    }

    cipher_txt[alpha_index] = '\0';
    return cipher_txt;
}

// Function to print the plain txt with 80 tokens per row
void PrintCipherText(char * cipher_txt) {
    printf("\nCiphertext:\n");
    long long len = strlen(cipher_txt);
    for (long long i = 0; i < len; i++) {
        printf("%c", cipher_txt[i]);
        if ((i + 1) % 80 == 0 || len - 1 == i) {
            printf("\n");
        }
    }
}

// Function to print the cipher txt with 80 tokens per row
void PrintPlainText(char * only_alpha) {
    printf("\nPlaintext:\n");
    long long len = strlen(only_alpha);
    for (long long i = 0; i < len; i++) {
        printf("%c", only_alpha[i]);
        if ((i + 1) % 80 == 0 || len - 1 == i) {
            printf("\n");
        }
    }
}

int main(int argc, char **argv) {
    // Process files and assign files to different variables
    if (argc != 3) {
        printf("Usage: %s <key_file> <plaintext_file>\n", argv[0]);
        return 1;
    }

    FILE *key_f = fopen(argv[1], "r");
    FILE *p_text_file = fopen(argv[2], "r");

    // Check if Null meaning that file is Null, string empty return, finish
    if (key_f == NULL) {
        printf("Error: %s\n", argv[1]);
        return 1;
    }

    if (p_text_file == NULL) {
        printf("Error: %s\n", argv[2]);
        fclose(key_f);
        return 1;
    }

    // Scan the key into a variable from the file
    int key_dim;
    fscanf(key_f, "%d", &key_dim);

    // This is the 2D chart, I did it dynamically with a double pointer
    int **hill_key = malloc(sizeof(int*) * key_dim);
    for (int i = 0; i < key_dim; i++) {
        hill_key[i] = malloc(sizeof(int) * key_dim);
    }

    // Print Key Matrix and send control to FillKeyFunction, close file
    printf("\nKey matrix:\n");
    FillKeyIn(key_f, hill_key, key_dim);
    fclose(key_f);

    char p_text[MAX_ARR_LEN] = {0};
    char character;
    int x = 0;

    // Delete \n characters for paragraphs and headers, close file of text after scanned
    while (fscanf(p_text_file, "%c", &character) != -1) {
        if (character == '\n'){
            continue;
        }
        p_text[x] = character;
        x++;
    }

    fclose(p_text_file);

    char *only_alpha = GetOnlyAlpha(p_text);
    int px_length = strlen(only_alpha);
    int mod = px_length % key_dim;
    int padding = key_dim - mod;
    int loop1 = px_length / key_dim;

    // Padding loop
    if (mod != 0) {
        for (int m = 0; m < padding; m++) {
            only_alpha[px_length + m] = 'x';
        }
        only_alpha[px_length + padding] = '\0';
    }

    // Print Plain Text with only alpha
    PrintPlainText(only_alpha);

    // Cipher txt pointer to function HillCipher, output assigned to the ptr
    char *cipher_txt = HillCipher(hill_key, only_alpha, key_dim, px_length, loop1 + (mod != 0));
    PrintCipherText(cipher_txt);

    // Free memory :)))))
    for (int fre = 0; fre < key_dim; fre++) {
        free(hill_key[fre]);
    }
    free(hill_key);
    free(only_alpha);
    free(cipher_txt);

    return 0;
}
/*=============================================================================
|   I Adan Rojas (5572801) affirm that this program is
| entirely my own work and that I have neither developed my code together with
| any another person, nor copied any code from any other person, nor permitted
| my code to be copied or otherwise used by any other person, nor have I
| copied, modified, or otherwise used programs created by others. I acknowledge
| that any violation of the above terms will be treated as academic dishonesty.
+=============================================================================*/