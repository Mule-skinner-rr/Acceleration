//
//  main.c
//  ch 8 program 2, resistor
//
//  Created by Ryan Roderick on 2/28/21.
//

/* From "Problem Solving and Program Design in C" by Jeri Hanly and Elliot Koffman, 7th Ed., 2013. */

/* page 512-13 */

/* A resistor is a circuit device designed to have a specific resistance value between its ends.  Resistance values are expressed in ohms or kilo-ohms.  Resistors are frequently marked with colored bands that encode their resistance values, as shown in Fig. 8.23.  The first two bands are digits, and the third is a power-of-ten multiplier.  The table below shows the meanings of each band color.  For example, if the first band is green, the second is black, and the third is orange, the resistor has a value of 50 x 10^3 ohms or 50k ohms.  The information in the table can be stored in a C++ program as an array of strings.

char COLOR_CODES[10][7] = {"black", "brown", "red", "orange", "yellow", "green", "blue", "violet", "gray", "white"};

Notice that "red" is 'COLOR_CODES[2]' and has  a digit value of 2 and a multiplier of 10^2.  In general, 'COLOR_CODES[n]' has digit value 'n' and multiplier value 10n.

Write a program that prompts for the colors of Band 1, Band 2, and Band 3, and then displays the resistance in kilo-ohms.  Include a helper function 'search' that takes three parameters--the list of strings, the size of the list, and a target string, and returns the subscript of the list element that matches the target or returns -1 if the target is not in the list.  Here is a short sample run:

"Enter the colors of the resistor's three bands, beginning with the band nearest the end.  Type the colors in lowercase letters only, NO CAPS.

 Band 1 => green
 Band 2 => black
 Band 3 => yellow
 Resistance value: 500 kilo-ohms
 Do you want to decode another resistor?
 => y
 Enter the colors of the resistor's three bans, beginning with the band nearest the end.  Type the colors in lowercase letters only, NO CAPS.
 Band 1 => brown
 Band 2 => vilet
 Band 3 => gray
 Invalid color: vilet
 Do you want to decode another resistor?
 => n
 
*/

/* I tab the trace statements in the program, and the traces in standard output. */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define ROWS 10
#define COLUMNS 7
#define BAND_MAX 3


void get_band_colors(char band_color[][COLUMNS]);

int search(const char COLOR_CODES[][COLUMNS], const char target[]);

int translate_to_numbers(int band_ints[BAND_MAX], const char band_colors[][COLUMNS], const char COLOR_CODES[][COLUMNS]);

double calc_resistance(double resistance, const int band_ints[]);

int main(int argc, const char * argv[])
{
    const char COLOR_CODES[ROWS][COLUMNS] = {"black", "brown", "red", "orange", "yellow", "green", "blue", "violet", "gray", "white"}; /* String constants */
    char band_colors[BAND_MAX][COLUMNS]; /* Each resistor has three color coded bands.  The user inputs them as strings each time the program runs. */
    int band_ints[BAND_MAX]; /* The program translates the band color strings into integers. */
    int i; /* 'i', increments up to 3 for this function's displays. */
    double resistance = 0.0; /* The program plugs in the numbers in the 'band_ints' array to calculate the 'resistance', so the value of 'resistance' changes with each iteration of the main function's 'while' loop. */
    int flag = 1; /* Flags weather the user's input is valid or not, and directs program flow. */
    char response = '\0'; /* Takes a yes or no response from the user to determine if they want to continue calculating resistors. */
    
    while (flag == 1)
    {
        /* Fills the string array 'band_colors' with character strings from standard input.  Each increment should have a string in it when it is done for a total of three. */
        get_band_colors(band_colors);
        
            /* Tracing statement: prints out 'band_colors'. */
            /* I tab the trace statements in the program, and the traces in standard output. */
            printf("     band_colors[i] = ");
            for(i=0; i < BAND_MAX; ++i)
            {
                printf("%s ", band_colors[i]);
            }
            printf("\n\n");
        
        /* Translates the color codes as strings to integers. */
        flag = translate_to_numbers(band_ints, band_colors, COLOR_CODES);
        

        if (flag == 1)
        {
            /* This for loop traces the character string translation to integers. */
            printf("     band_ints[i] = ");
            for(i=0; i < BAND_MAX; ++i)
            {
                printf("%d ", band_ints[i]);
            }
            printf("\n\n");
            
            resistance = calc_resistance(resistance, band_ints);
            
            printf("Resistance value: %.0f kilo-ohms \n\n", resistance);
        } /* Calls the calculation function.  'flag' is used, but does not change.  Populates and prints 'resistance' for each iteration of the 'while' loop. */
        
        /* Either valid or invalid, the program continues to the next statements, so the statement does not need an 'else'. */
        
        printf("Enter 'y' to decode another resistor: \n");
        printf("=> ");
        
        /* Populates 'response' from standard input. */
        scanf(" %c", &response);
        
        
        if (toupper(response) == 'Y')
            flag = 1;
        else
            flag = 0;
        /* 'flag' changes to 1 or 0 and determines if the loop will continue. */
    }
    
    return 0;
}

/* This function modifies and returns 'resistance'.  It only uses the values in 'band_ints[]'.  It overwrites 'exponent' each time the program runs, but does not use it outside of the function. */
double calc_resistance(double resistance, const int band_ints[])
{
    double exponent = band_ints[2];

    resistance =  ((band_ints[0] * 10) + band_ints[1]) * pow(10.0, exponent);
    
        /* Trace statements to break down the calculation */
        printf("Calculation step by step: \n");
        printf("     ((band_ints[%d] * 10) + band_ints[%d]) =\n\t  %d \n\n", band_ints[0], band_ints[1], ((band_ints[0] * 10) + band_ints[1]));
        
        printf("     * (pow(10.0, %.0f)) =\n\t  %lf \n\n", exponent, pow(10.0, exponent));
    

        
        printf("     = %.0f / 1000 \n\n", resistance);
    
    resistance = resistance / 1000;
        
        printf("     resistance = %.0f \n\n", resistance);
    
    return(resistance);
}

/* Populates/overwrites 'band_ints' and uses it.  Only uses 'band_colors' and 'COLOR_CODES'. */
int translate_to_numbers(int band_ints[BAND_MAX], const char band_colors[][COLUMNS], const char COLOR_CODES[][COLUMNS])
{
    int i;
    int band_number = -1; /* Will hold values 0 through nine or -1. */
    int flag = 1; /* Will hold values 0 or 1. */
    
    /* This loop uses 'COLOR_CODES' and 'band_colors' to populate 'band_number', which populates 'band_ints[i]' in turn.  The loop overwrites it and discards it.  The loop also uses 'band_number' to stop the loop upon invalid entry.  The loop returns 'flag' to stop the entire program upon invalid entry. */
    for (i = 0; i < BAND_MAX; ++i)
    {
        band_number = search(COLOR_CODES, band_colors[i]);
        
            printf("     The increment number of color string from COLOR_CODES stored in 'band_number' is %d \n\n", band_number);
        
        if (band_number == -1)
        {
            printf("Invalid entry: %s \n", band_colors[i]);
            flag = 0;
            break; /* Breaks out of the 'for' loop and sends the program back to the 'main' function to ask if the user wants to check another resistor.  Otherwise, the function will continue on, assigning -1 to 'band_ints[]' and looping on to the next 'search' function and assignment. */
        }
        
        band_ints[i] = band_number;
    }
    
    return(flag);
}

/* 'target' will be a string matching any of the 10 color possibilities for a resistor band that are in 'string_array', unless it is misspelled or not on the list. */
int search(const char string_array[][COLUMNS], const char target[])
{
    int i; /* used as a counter and reset at the beginning of each function run. */
    int found = 0; /* Used to control the 'while' loop and return the increment number where the 'target' is.  Holds values 0 through 9 or -1.  It still works if it finds the color at the 0 increment because that number would be returned and would thusly stop the loop anyway and -1, not 0, will stop the program. */
    
    
            printf("     Compare 'COLOR_CODES' to 'band_colors[%s]': \n", target);
    i = 0;
    while (!found && i < ROWS)
    {
            printf("     %s vs. %s \n", string_array[i], target);
        
        if (strcmp(string_array[i], target) == 0)
        {
            found = i;
            
            return(found);
            
        } else
            ++i;
    }
    found = i;
    /* The 'while' loop uses 'string_array[i]' and 'target' to compare, but does not change them.  The loop uses 'i' and 'ROWS' to control the loop, and it uses 'i' as an increment variable, discarding it after capturing it's value in 'found', a variable that the loop returns. */
    
    
    if (found == ROWS)
    {
        found = -1;
    }
    
    return(found);
}

/* 'band_colors' is used and returned with strings from standard input. */
void get_band_colors(char band_colors[][COLUMNS])
{
    int i; /* loop counter */

    
    printf("Enter the colors of the resistor's three bands, beginning with the band nearest the end.  Type the colors in lowercase letters only, NO CAPS. \n");
    
    /* This gets the band colors in character form. */
    for (i = 0; i < BAND_MAX; ++i)
    {
        printf("Band %d => ", i+1);
        scanf("%s", band_colors[i]);
    }
    /* The loop populates 'band_colors' with strings from standard input.  'i' controls the loop, along with 'BAND_MAX', to limit iterations.  And, 'i' increments through the rows of the 'band_colors' string array.  The loop uses 'i' and overwrittes it in subsequent iterations.  The loop uses and returns 'band_colors' as an output array. */
    
}
