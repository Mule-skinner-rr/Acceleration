//
//  main.c
//  ch 8 program 7, reverses
//
//  Created by Ryan Roderick on 4/5/21.
//

/* From "Problem Solving and Program Design in C" by Jeri Hanly and Elliot Koffman, 7th Ed., 2013. */

/* page 515 */

/* Write a program that takes data a line at a time and reverses the words of the line.  For example,
 
    Input: birds and bees
    Reversed: bees and birds
 
   The data should have one blank between each pair of words.8
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define LENGTH 100
#define SENTINEL "quit"

void prompt(void);

char * scanline(char * input);

int make_list(char word_list[LENGTH][LENGTH], char input[LENGTH]);

void reverse_display(char word_list[LENGTH][LENGTH], int list_increment);

int main(int argc, const char * argv[])
{
    char input[LENGTH];
    char word_list[LENGTH][LENGTH];
    int list_increment;
    
    prompt();
    
    while (strcmp(input, SENTINEL) != 0)
    {
        /* User types in a line of words, like "birds and bees". */
        scanline(input);
        list_increment = make_list(word_list, input);
        printf("list_increment = %d \n\n", list_increment);
        reverse_display(word_list, list_increment);
        prompt();
    }
    
    return (0);
}

void prompt(void)
{
    printf("Please enter \"quit\" or a sequence of words that you would like reversed: \n");
}

/* from page 484 */
/* populates string variable 'input' one character at a time. */
char * scanline(char * input)
{
    int i, ch;
    
    i = 0;
    for (ch = getchar();
         ch != '\n' && ch != EOF && i < LENGTH - 1;
         ch = getchar())
    {
        input[i++] = ch;

    }
    input[i] = '\0';
    
    return (input);
}

int make_list(char word_list[LENGTH][LENGTH], char input[LENGTH])
{
    int row;
    int column;
    int start_at = 0;
    int list_increment = 0;
    
    row = 0;
    for (column = 0; column <= strlen(input); ++column)
    {
        if (input[column] == '\0')
        {
            strcpy(word_list[row], &input[start_at]);
        }
        
        if (isspace(input[column]))
        {
            strncpy(word_list[row], &input[start_at], column - start_at);
            
            word_list[row][column - start_at] = '\0';
                        
            printf("word_list[%d] = %s \n", row, word_list[row]);
            
            start_at = column + 1;
            
            ++row;
            
            printf("start_at = %d \n", start_at);
        }
    }
    
    
    list_increment = row;
    
    return(list_increment);
}

void reverse_display(char word_list[LENGTH][LENGTH], int list_increment)
{
    int row;
    
    printf("Reversed: ");
    for (row = list_increment; row >= 0; --row)
    {
        printf("%s ", word_list[row]);
    }
    printf("\n\n");
}

/*
 There are a couple of different ways to do this.  At first I tried to copy all the words into a new, reversed, string.  But, that gave me two edge cases: at the end and the beginning.  So, I decided to scan the words into an array of strings so that I could print out the list in reverse order.
 That worked well, but there was still an edge case: to copy in the last word, I wrote a condidtion that if the input character at a given 'column' point was the null character, the program would copy the rest of the line from the starting point to that null character, adding its own null character with the 'strcpy' function.
 Solving this problem gave me a lot of practice with dealing with the integers that 'strlen()', '&insert[column]' and 'word_list[row]' represent, which really helped me remember their differences.
 */
