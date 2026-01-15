#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include<stdbool.h>

int returnNumberOfSpaces(char*);
char* returnReversedWord(char*, int);
char* returnSwappedWord(char*, int);
char* returnModifiedWord(char*, bool);
char* returnWord(int, int, char*);
bool isVowel(char);

int main () {
//                "01 2 45 78910 1213 15_16_17_18_19_20"
    char* input = malloc(200 * sizeof(char));
    char* result;
    int number_of_words;
    int length_of_input;

    printf("Hello, this program is created for translating a given sentence into PigLatin.\n");

    // Get input 
    printf("\nPlease enter your sentence: ");
    scanf("%99[^\n]", input);

    // Get number of chars in the sentence 
    length_of_input = strlen(input) + 1;
    printf("\nThere are %d characters in the given sentence.\n", length_of_input);

    // Get number of words in the sentence 
    number_of_words = returnNumberOfSpaces(input) + 1;
    printf("\nThere are %d words in the given sentence.\n", number_of_words);

    // Get the words
    int space_number = 1;
    int index = 0;
    int end = 0;
    int start = 0;
    bool beginsWithVowel = false;
    char* word = malloc(length_of_input * sizeof(char));
    result = malloc((length_of_input + 3 * number_of_words) * sizeof(char)); 
    
    for (int i = 0; i < number_of_words; i++) {
        // Move to the next char if space char is encountered   
        if (input[index] == ' ') {
            index++;
            end++;
        }

        start = index;
        while (input[index] != ' ') {
            // Check for the EOF of the input
            if (input[index] == '\0')
                break;

            index++;
            end++;
        }

        // Checks
        // printf("\n[%d]: Start(%d) and End(%d)", i, start, end);

        // Get the word
        int len = (end - start);
        char* temp_word = malloc((len + 3) * sizeof(char));
        char* reversed_word = malloc(len * sizeof(char));

        // The word retrieved
        temp_word = returnWord(start, end, input);
        printf("\nWord [%d]: %s", i, temp_word);

        // Check if begins with vowel
        beginsWithVowel = isVowel(tolower(temp_word[0]));

        // The reversed word
        temp_word = returnSwappedWord(temp_word, len);
        printf("\nReverded Word [%d]: %s", i, temp_word);

        // The modified word
        temp_word = returnModifiedWord(temp_word, beginsWithVowel);
        printf("\nModified Word [%d]: %s\n", i, temp_word);

        // Construct/Add result
        if (i == 0) 
            result = temp_word;
        else {
            result = strcat(result, " ");
            result = strcat(result, temp_word);
        }

        if (index == length_of_input)
            break;
    }

    printf("\nResult: %s", result);
    putchar('\n');

    return 0;
}

char* returnWord(int start, int end, char* input) {
    int length = (end - start) + 1;
    int index = 0;
    char* word = malloc(length  * sizeof(char));
    
    for (int i = start; i < end + 1; i++) {
        if (isspace(word[i]))
            i++;

        word[index] = input[i];
        index++;
    }

    return word;
}

int returnNumberOfSpaces(char* string) {
    int i = 0;
    int count = 0;
    while (string[i] != '\0') {
        if (string[i] == ' ')
            count += 1; 

        i++;
    }

    return count;
}

char* returnSwappedWord(char* word, int length) {
    char* reversed_word = malloc(length * sizeof(char));
    int index = 0;
    char punctuation;
    bool punct_available = false;
    char temp;

    // If starts with a vowel, return as it is
    if (isVowel(tolower(word[0]))) 
        return word;

    if (ispunct(word[length - 1])) {
        punctuation = word[length -1];
        length -= 1;
        punct_available = true;
    }

    // Move the consonant to the end of the word
    temp = word[0];
    for (int i = 1; i < length && word[i] != '\0'; index++, i++) {
        reversed_word[index] = word[i];
    }

    reversed_word[length - 1] = temp;
    index += 1; 

    if (punct_available) {
        reversed_word[index] = punctuation;
    }

    return reversed_word;
}


char* returnReversedWord(char* word, int length) {
    char* reversed_word = malloc(length * sizeof(char));
    int index = 0;
    char punctuation;
    bool punct_available = false;

    // If starts with a vowel, return as it is
    if (isVowel(word[0])) 
        return word;

    if (ispunct(word[length - 1])) {
        punctuation = word[length -1];
        length -= 1;
        punct_available = true;
    }

    for (int i = length - 1; i >= 0; index++, i--) {
        reversed_word[index] = word[i];
    }

    if (punct_available) {
        reversed_word[index] = punctuation;
    }

    return reversed_word;
}

char* returnModifiedWord(char* word, bool beginsWithVowel) {
    int length = strlen(word);
    int _length;
    char* new_word = malloc((length + 3) * sizeof(char));
    char* vowel_str = "yay";
    char* consonant_str = "ay";
    char punctuation;
    bool has_punct = false;

    // Check for punctuation
    for (int i = 0; i < length; i++ ) {
        if (ispunct(word[i])) {
            punctuation = word[i];
            has_punct = true;
            _length = i;
            word = returnWord(0, i - 1, word);
            break;
        }
    }
    
    // Check for whitespaces
    for (int i = 0; i < length; i++ ) {
        if (isspace(word[i])) {
            word = returnWord(0, i - 1, word);
            break;
        }
    }

    if (beginsWithVowel) 
        new_word = strcat(word, vowel_str);
    else 
        new_word = strcat(word, consonant_str);

    // Insert the punct back
    // length = strlen(new_word);
    if(has_punct && beginsWithVowel) {
        new_word[_length + 3] = punctuation;
    } else if (has_punct) {
        new_word[_length + 2] = punctuation;
    }

    return new_word;
}

bool isVowel(char input) {
    char vowels[5] = {'a', 'e', 'i', 'o', 'u'};

    for (int i = 0; i < 5; i++) {
        if (input == vowels[i])
            return true;
    }

    return false;
} 