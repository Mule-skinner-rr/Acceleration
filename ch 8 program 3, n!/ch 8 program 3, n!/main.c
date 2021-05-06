//
//  main.c
//  ch 8 program 3, n!
//
//  Created by Ryan Roderick on 3/12/21.
//

/* From "Problem Solving and Program Design in C" by Jeri Hanly and Elliot Koffman, 7th Ed., 2013. */

/* page 514 */

/* 3. Write a funciton 'fact_calc' that takes a string output argument and an interger input argument 'n' and returns a string showing the calculation of n!.
 
 For example, if the value supplied for 'n' were 6, the string returned would be "6! = 6 X 5 X 4 X 3 X 2 X 1 = 720".
 
 Write a program that repeatedly prompts the user for an integer between 0 and 9, calls 'fact_calc' and outputs the resulting string in a box of asterisks of the right size to surround the result.
 
 If the user inputs an invalid value, the program should display an error message and reprompt for valid input.  Input of the sentinel -1 should cause the input loop to exit.  Sample run:
 
   "Enter an integer between 0 and 9 or -1 to quit => 6
    **************************************
    * 6! = 6 X 5 X 4 X 3 X 2 X 1 = 720 *
    **************************************
    Enter an integer between 0 and 9 or -1 to quit => 12
    Invalid entry
    Enter an integer between 0 and 9 or -1 to quit=> 0
    ************
    * 0! = 1 *
    ************
    Enter an integer between 0 and 9 or -1 to quit => -1"
 
 */

#include <stdio.h>
#include <string.h>

#define COLUMNS 52 /* In this program, the string length for a factorial of 9 is 51, so COLUMNS needs to hold 52 elements in order to include the null character. */

void fact_calc(char calc[COLUMNS], const int n); /* The program only sends 'calc' to the assemble and display functions.  The assignment asks that 'fact_calc' take a string output argument, so here it is. */

int assemble_calc(char calc[COLUMNS], const int factorial, const int n);

void display_calc(const char calc[COLUMNS]);


int main(int argc, const char * argv[])
{
    char calc[COLUMNS];
    int n; /* The number for the factorial. */
    int sentinel = -1; /* Input to quit the program. */
    
    /* Populates 'n' with an integer and tests input. */
    printf("Enter an integer between 0 and 9 or -1 to quit => \n");
    scanf("%d", &n);
    
    while (n != sentinel)
    {
        if (n < 0 || n > 9) {
            
            printf("Invalid input \n");
            printf("Enter an integer between 0 and 9 or -1 to quit => \n");
            scanf("%d", &n);
            
        } else {
            
            fact_calc(calc, n);
            /* The function populates 'calc' with a factorial calculation string. */
            
            display_calc(calc);
            
            /* Populates 'n' with an integer to calculate. */
            printf("Enter an integer between 0 and 9 or -1 to quit => \n");
            scanf("%d", &n);
        }
    }
    
    return 0;
}


void fact_calc(char calc[COLUMNS], const int n)
{
    int factorial;
    int complete;
    int i;
    
    i = n; /* 'i' resets for each call to this function, which uses it as a decrement counter. */
    
    /* Calculates factorial and echo print */
    for (factorial = i; i > 1; --i)
    {
        factorial = factorial * (i - 1);
        printf("(n - 1) = %d, factorial = %d \n", (i - 1), factorial);
    }
    
    /* Calls the function to assemple the calculation string. */
    complete = assemble_calc(calc, factorial, n); /* 'complete' takes the value of 'n'.  The program does not do anything with this number, but returning an interger allows 'fact_calc' to exit early for edge case inputs 0 and 1. */

}


int assemble_calc(char calc[COLUMNS], const int factorial, const int n)
{
    int i; /* counter */
    char temp[COLUMNS]; /* The program fills this string with */

    /* Populates 'calc' for inputs 0 or 1. */
    if (n == 0 || n == 1) {
        
        sprintf(calc, "%c%c%d", '*', ' ', n);
        strcat(calc, "! = 1 *");
                
        return(n); /* stops function with a zero or one print out. */
        
    /* For integers 2 through 9, populates the first part of the factorial for 'calc'. */
    } else {
        
        /* The initial part of each calculation: */
        sprintf(calc, "%c%c%d%c%c%c%c%d%c", '*', ' ', n, '!', ' ', '=', ' ',  n, ' ');
    
        i = 1;
        /* Populate 'temp' with each next factorial multiplier, then concatenates that onto 'calc', which has a length of COLUMNS.  For a factorial of 9, 'calc' needs at least 52 increments, 0-51, including the null character. */
        while (i < n)
        {
            /* Translates the integers into characters then populates 'temp' with the string and concatenates 'temp' to 'calc' until the factorial numbers reach 1. */
            sprintf(temp, "%c%c%d%c", 'X', ' ', (n - i), ' ');
            
            strcat(calc, temp);

            ++i;
        }
        
        /* Concatenates the string onto 'calc' */
        strcat(calc, "= ");
        
        sprintf(temp, "%d", factorial);
        strcat(calc, temp);
        
        /* Translate integer and copy string into 'temp'. */
        strcat(calc, " *");
    
    }
    
    return(n);
}


void display_calc(const char calc[COLUMNS])
{
    int i; /* counter */
    
    /* Top line of asterisks. */
    /* 'i' increments through the length of 'calc'. */
    for (i = 0; i < strlen(calc); ++i)
    {
        printf("*");
    }
    printf("\n");
    
    /* Factorial calculaiton string print out with an asterisk on each end to complete the box. */
    printf("%s \n", calc);
    
    /* Bottom line of asterisks. */
    /* 'i' increments through the length of 'calc'. */
    for (i = 0; i < strlen(calc); ++i)
    {
        printf("*");
    }
    printf("\n");

}
