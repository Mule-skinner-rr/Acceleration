//
//  main.c
//  ch 8 program 5, plurals
//
//  Created by Ryan Roderick on 3/17/21.
//

/* From "Problem Solving and Program Design in C" by Jeri Hanly and Elliot Koffman, 7th Ed., 2013. */

/* page 514-15 */

/* 5. Write a program that takes nouns and forms their pliurals on the basis of these rules:
 
 a. If the noun ends in "y", remove the "y" and add "ies".
 b. If the noun ends in "s", "ch", or "sh", add "es".
 c. In all other cases, just add "s".
 
 Print each noun and its plural.  Try the following data.
 
    chair  diary  boss  circus  fly  dog  church  clue  dish
 
 */

#include <stdio.h>
#include <string.h>

#define LENGTH 30

int determine_ending(const char noun[], const char endings[][LENGTH]);

void make_plural(char plural_form[], const char noun[], const char suffixes[][LENGTH], const int index);

void display(const char noun[], const char plural_form[]);

/* Gives the program a word to make plural in a loop. */
int main(int argc, const char * argv[])
{
    char noun[LENGTH];
    const char endings[][LENGTH] = {"y", "s", "ch", "sh"};
    const char suffixes[][LENGTH] = {"ies", "es", "s"};
    char plural_form[LENGTH]; /* The program could have used and modified 'noun' and cut down on one variable, but using an additional variable for the 'plural_form' of the noun makes it easier to understand what state the word is in. */
    
    int index; /* can equal 0 to 4, including the alternative case for 'endings'. */
    char quit[] = "quit";
    
    
    printf("Please enter a noun or \"quit\": \n");
    scanf("%s", noun);
    
    while(strncmp(noun, quit, 4) != 0) /* The 'n' in 'strncmp' limits the comparison so I don't unintentionally read an end of line character or something and get the incorrect comparison. */
    {
        /* Populates 'index' with an integer from 0 to 4 for the 'switch' statement in 'make_plural'. */
        index = determine_ending(noun, endings);
        
        /* Assembles and returns the 'plural_form' of the noun. */
        make_plural(plural_form, noun, suffixes, index);
        
        printf("plural = %s \n", plural_form);
        
        printf("Please enter a noun or \"quit\": \n");
        scanf("%s", noun);
    }
    
}

void display(const char noun[], const char plural_form[])
{
    printf("The word %s in its plural form is %s. \n\n", noun, plural_form);
}

/* Returns the 'plural_form' of the 'noun' */
void make_plural(char plural_form[], const char noun[], const char suffixes[][LENGTH], const int index)
{
    /* Copy 'noun' into 'plural' */
    strcpy(plural_form, noun);
    
    switch (index) {
        case 0:
            /* Copies "ies" onto the noun, overwriting the "y". */
            /* With '&plural_form[strlen(plural_form) - 1]', the program is pointing to a single increment in the single row character string.  In this case, it is pointing to the character before the last character in the string, "y", so that it can add "i" in its place, in addition to "es" in the next two increments.  'suffixes[0]' points to the string, "ies", at increment 0 in 'suffixes', an array of strings, which is by definition multidimensional. */
            strcpy(&plural_form[strlen(plural_form) - 1], suffixes[0]);
            break;
            
        case 1:
        case 2:
        case 3:
            /* Concatenates "es" to the noun string. */
            strcat(plural_form, suffixes[1]);
            break;
        
        default:
            /* Concatenates an "s" to 'plural', overwriting the "y". */
            strcat(plural_form, suffixes[2]);
    }
}

/* Sends back an integer representing the ending of the noun and which suffix it will get.  The function uses two 'for' loops, one to check for "y" or "s", the other, "ch" or "sh". */
int determine_ending(const char noun[], const char endings[][LENGTH])
{
    long int letters; /* sum */
    int index = 0; /* flag holds values of 0 - 4 */
    int i; /* counter, 0 - 3 */
    
    /* Populaters 'letters' with the length of the 'noun'. */
    letters = strlen(noun);
    
    /* Subtracts one from 'letters' to get the second to last increment number of 'noun', and compares that to the possible word endings "y" then "s" that the program stored in increments 0 or 1 of 'endings'. */
    for (i = 0; i < 2; ++i)
    {
        /* Here, 'strncmp' is using the "address of" operator, &, to point to a specific character in the row of characters in 'noun'.  It is saying, "Starting after this specific increment, compare the letter there to the letter in 'endings' at increment 'i'."  The comparison uses a 1 as its third argument to limit the comparison to that one letter.  */
        if (strncmp(&noun[letters - 1], endings[i], 1) == 0)
        {
            /* If the word ends in "y" or "s", 'index' takes the increment 0 or 1, respectively. */
            index = i;
            printf("index = %d \n", index); /* trace statement */
            return(index); /* "y" returns 0, "s" returns 1. */
            break;
        }
    }
    
    for (i = 2; i < 4; ++i)
    {
        /* This comparison works the same as the one before except that it is comparing two characters instead of just one, which is why its third argument is a 2. */
        if (strncmp(&noun[letters - 2], endings[i], 2) == 0)
        {
            /* Populates 'index' with 2 or 3, which match "ch" and "sh" in 'endings'. */
            index = i;
            printf("index = %d \n", index);
            return(index);
            break;
        }
    }
    /* If the program gets here, the 'noun' doesn't have any of the 'endings', so it indicates a 4 for the switch statement in 'make_plural'. */
    index = 4;
    printf("index = %d \n", index);

    return(index);
}

/* In this program I learned how to add arguments to 'strncmp' so that it compares only one specific character in a string, either within a single row character array or multidimensional array. */
