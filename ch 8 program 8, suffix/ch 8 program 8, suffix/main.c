//
//  main.c
//  ch 8 program 8, suffix
//
//  Created by Ryan Roderick on 4/10/21.
//

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define LENGTH 50

void introduction(void);

void get_word(char word[]);

void match_suffix(char suffix[], char word_one[], char word_two[], int length);

void display_result(char suffix[]);

void display_exit(void);

int main(int argc, const char * argv[])
{
    int length = 50;
    char word_one[length];
    char word_two[length];
    char suffix[length];
    char sentinel[] = "quit";
    
    introduction();
    
    get_word(word_one);
    
    /* Getting the words separately allows the program to prompt the user once, check that they do not want to quit, and continually take each entry of two words until the user quits. */
    while (strcmp(word_one, sentinel) != 0)
    {
        get_word(word_two);
        
        match_suffix(suffix, word_one, word_two, length);
                
        display_result(suffix);
        
        get_word(word_one);
    }
    
    display_exit();
    
    return 0;
}

void introduction(void)
{
    printf("This program compares the endings of two words and returns the portion of each ending that matches.  \n");
    
    printf("Enter two words, separated by a space, \n or \"quit\" when done: \n\n");
}

/* The code just looks cleaner with a separate function for this. */
void get_word(char word[])
{
    scanf("%s", word);
}

/*
 This function is the key to solving the problem.  It gets the lengths of the words and checks the exception that there are no common endings.  Then, the function increments back through the word, comapring each letter until a mismatch is found.
 To save the common letters at the end of the word, the string copy function increments one letter forward in the first word and sends back the "suffix", which is just the last common letters in any two words and may just happen to be a proper suffix.
 There are a set number of suffixes in English.  For example, "tion" is a suffix, along with "s", "es", and "ing".  The end letters from one of the book test runs is "stination".  That is not a suffix, but it is a common set of letters in the end portion of the two words that the program compares.
 */
void match_suffix(char suffix[], char word_one[], char word_two[], int length)
{
    long int i, j;
    
    i = strlen(word_one) - 1;
    j = strlen(word_two) - 1;
    
    if (word_one[i] != word_two[j])
    {
        strcpy(suffix, " ");
       
    } else if (word_one[i] == word_two[j]) {
        
        while (word_one[i] == word_two[j])
        {
            --i;
            --j;
        }
        
        strcpy(suffix, &word_one[++i]);
    }
    
}

void display_result(char suffix[])
{
    int i;
    
    if (strcmp(suffix, " ") == 0) {
        
        printf("\nThe endings do not match. \n\n");
        
    } else {
    
        printf("\nThe ending protion that matches: \n-");
        
        for (i = 0; i < strlen(suffix); ++i)
        {
            printf("%c", toupper(suffix[i]));
        }
        printf("\n\n");
    }
}

void display_exit(void)
{
    printf("\nPlease re-run the program to check more words. \n\n");
}

/*
 This program taught me how to compare specific letters in different words.  At first I tried to use the string compare function in the 'while' statement, but I got a bad access thread error.  Finally, reviewing the basics of string comparison on page 474, I realized that I should compare letters themselves with the simpler "equal to" operator, '=='.
 
 I also spent some time getting the user interface just the way I wanted it.
 */
