//
//  main.c
//  ch 8 program 4, 'hydroxide'
//
//  Created by Ryan Roderick on 3/17/21.
//

/* From "Problem Solving and Program Design in C" by Jeri Hanly and Elliot Koffman, 7th Ed., 2013. */

/* page 514 */

/* 4. Write and test a function, 'hydroxide', that returns a 1 for true if its string argument ends in the substring 'OH'.  Try the function hydroxide on the following data:
 
    KOH  H202  NaCl  NaOH  C9H8Of  MgOH
 
 */

#include <stdio.h>
#include <string.h>

#define LENGTH 10

int hydroxide(char chemical[LENGTH]);

int main(int argc, const char * argv[])
{
    char chemical[LENGTH];
    int answer;
    char sentinel[10] = "quit";
    
    printf("Please enter a chemical element or 'quit' to quit: \n");
    scanf("%s", chemical);
    
    /* Populates 'answer' */
    while (strcmp(chemical, sentinel) != 0)
    {
        answer = hydroxide(chemical);
        
        if (answer == 1)
            
            printf("Yes, %s includes hydroxide. \n\n", chemical);
        
        else if (answer == 0)
            
            printf("No, %s doesn't include hydorxide. \n\n", chemical);
        
        printf("Please enter a chemical element or 'quit' to quit: \n");
        scanf("%s", chemical);
    }
    
    return 0;
}

int hydroxide(char chemical[LENGTH])
{
    int answer = 0;
    char hydroxide[LENGTH] = "OH";
    int i; /* counter */
    
    if (strlen(hydroxide) > strlen(chemical))
    {
        answer = 0;
       
    } else {
        
        for (i = 0;
             i <= strlen(chemical) - strlen(hydroxide);
             ++i)
        /* The comparison needed to be less than or equal to,'<=', because the length of the 'chemical' minus the length of 'hydroxide' equals exactly enough elements to compare 'hydroxide' to the 'chemical' */
        {
            /* Compares the number of elements in 'hydroxide' to the same number of elements at each increment of 'chemical'. */
            if (strncmp(hydroxide, &chemical[i], strlen(hydroxide)) == 0)
            {
                answer = 1;
                break;

            } else
                answer = 0;
        }
    }
    
    return(answer);
}
