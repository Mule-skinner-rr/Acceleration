//
//  main.c
//  Ch 8 program 1, de_blank
//
//  Created by Ryan Roderick on 1/17/21.
//

/* From "Problem Solving and Program Design in C" by Jeri Hanly and Elliot Koffman, 7th Ed., 2013. */

/* page 512 */

/* Write and test a function 'de_blank' that takes a string ouput and string input argument and returns a copy of the input argument with all blanks removed. */

#include <stdio.h>
#include <string.h>

void de_blank(char input_string[], char output_string[]);

int main(int argc, const char * argv[])
{
    const int length = 30;
    char input_string[length] = "one two three four";
    char output_string[length];
    
    printf("input_string length = %lu \n\n", strlen(input_string));
    
    de_blank(input_string, output_string);

    
    printf("%s \n\n", output_string);
    
    return 0;
}

void de_blank(char input_string[], char output_string[])
{
    int first;
    int next;
    int found;
    
    first = 0;
    found = 0;
    
    for (next = 0; next < strlen(input_string) && !found; ++next)
    {
        if (input_string[next] == ' ')
        {
            strncpy(output_string, input_string, next - first);
            
            output_string[next] = '\0';
            
            first = next + 1;
            found = 1;
        }
    }
    
    for (++next; next <= strlen(input_string); ++next)
    /* I needed to change the comparison operator to include 'less than or equal to' in order to get the loop to rotate up to the 18th increment.  */
    /* On its last round, 'next' equals 17, which is a character, not the NULL character.  The loop never seems to run the comparison for the 18th increment, which is where the '\0' is.  The loop does not copy the last part of the string without the NULL condition in the loop, so I am not understanding something. */
    {
        if (input_string[next] == ' ' || input_string[next] == '\0')
        {
            strncat(output_string, &input_string[first], next - first);
            
            printf("next = %d \n\n", next);
            first = next + 1;
            
        }
    }
    
    
}
