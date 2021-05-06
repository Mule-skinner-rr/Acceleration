//
//  main.c
//  ch 8 program 6, name, age
//
//  Created by Ryan Roderick on 3/22/21.
//

/* From "Problem Solving and Program Design in C" by Jeri Hanly and Elliot Koffman, 7th Ed., 2013. */

/* Write a program that stores lists of names (the last name first) and ages in parallel arrays and sorts the names into alphabetical order, keeping the ages with the correct names.  Sample output:
 
 Original list
 ------------------------
 Ryan, Elizabeth    62
 McIntyre, Osborne  84
 DuMond, Kristin    18
 Larson, Lois       42
 Thorpe, Trinity    15
 Ruiz, Pedro        35
 
 Alphabetized list
 -----------------------
 DuMond, Kristin    18
 Larson, Lois       42
 McIntyre, Osborne  84
 Ruiz, Pedro        35
 Ryan, Elizabeth    62
 Thorpe, Trinity    15
 
 */

/* This program is mostly a copy of FIGURE 8.14, page 479. */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXAPP 50 /* Maximum number of applicants */
#define STRING_SIZE 50
#define SENTINEL "quit"

int get_applicants(char names[][STRING_SIZE], int ages[MAXAPP]);

void make_copy(char names_copy[][STRING_SIZE], const char names[][STRING_SIZE], const int number);

void make_capitals(char names_copy[][STRING_SIZE], const int number);

void assign_pointers(char * names_pointer[MAXAPP], int * ages_pointer[MAXAPP], char names[][STRING_SIZE], int ages[MAXAPP], const int number);

void select_sort_string(char * names_pointer[MAXAPP], char names_copy[][STRING_SIZE], int * ages_pointer[MAXAPP], const int number);

int alpha_first(char names_copy[][STRING_SIZE], const int fill_sub, const int number);

void display(char * names_pointer[], int * ages_pointer[], const char names[][STRING_SIZE], const int ages[MAXAPP], const int number);


int main(int argc, const char * argv[])
{
    int number;
    char names[MAXAPP][STRING_SIZE];
    char names_copy[MAXAPP][STRING_SIZE];
    char *names_pointer[MAXAPP];
    int ages[MAXAPP];
    int *ages_pointer[MAXAPP];

    number = get_applicants(names, ages);
    
    if (number == 0)
        return (0);
        
    make_copy(names_copy, names, number);
    
    make_capitals(names_copy, number);
    
    assign_pointers(names_pointer, ages_pointer, names, ages, number);
    
    select_sort_string(names_pointer, names_copy, ages_pointer, number);
    
    display(names_pointer, ages_pointer, names, ages, number);
    
    return 0;
}

/* Populates 'number', 'names[]', and 'ages[]', and returns the actual number of applicants. */
int get_applicants(char names[][STRING_SIZE], int ages[MAXAPP])
{
    int i; /* Will increment to no more than MAXAPP. */
    int number = 0; /* Counts the actual number of applicants. */
    char last[STRING_SIZE], first[STRING_SIZE]; /* Temporarily holds each name. */
    
    
    printf("Please enter the names and ages of up to %d total applicants, last name first, like this: \n> Doe, John 35 or \"%s\" to exit. \n> ", MAXAPP, SENTINEL);
    
    /* Checks for the sentinel value and populates string variables 'last', and 'first', and 'ages[]', then assembles the 'names[]' array with the names in this format: "Doe, John".  The names and ages arrays run parallel in this program and will follow the 'names_copy' lead. */
     i = 0;
     for (scanf("%s", last);
          strcmp(last, SENTINEL) != 0 && i < MAXAPP;
          scanf("%s", last))
     {
         scanf("%s%d", first, &ages[i]);
         strcpy(names[i], last);
         strcat(names[i], " ");
         strcat(names[i], first);
         ++i;
         printf("> ");
     }
     
     number = i;
     
     return (number);
}

/* Populates 'names_copy[]'. */
void make_copy(char names_copy[][STRING_SIZE], const char names[][STRING_SIZE], const int number)
{
    int i;
    
    for (i = 0; i < number; ++i)
    {
        strcpy(names_copy[i], names[i]);
    }
}

/* Makes 'names_copy[][]' all capitals for comparison.
 Function 'alpha_first' will compare these capitalized names and send back an integer for the pointer array, which points to the original list of names. */
void make_capitals(char names_copy[MAXAPP][STRING_SIZE], const int number)
{
    int i, j; /* 'i' for rows.  'j' for columns. */
    
    for (i = 0; i < number; ++i)
    {
        for (j = 0; j < strlen(names_copy[i]); ++j)
        {
            if (islower(names_copy[i][j]))
            {
                names_copy[i][j] = toupper(names_copy[i][j]);
            }
        }
    }
    
}

/* Copies memory addresses from the pointer variables to the original array, so that the program can arrange the pointer addresses in alphabetical order and keep the original array in its original order. */
void assign_pointers(char * names_pointer[MAXAPP], int * ages_pointer[MAXAPP], char names[][STRING_SIZE], int ages[MAXAPP], const int number)
{
    int i;
    
    for (i = 0; i < number; ++i)
    {
        names_pointer[i] = names[i];
        ages_pointer[i] = &ages[i];
        /* Copies addresses only. */
    }
}

/* Alphabetizes the capitalized copy of the applicants' names, the names pointer and the ages pointer, all in the same loop. */
void select_sort_string(char * names_pointer[MAXAPP], char names_copy[][STRING_SIZE], int * ages_pointer[MAXAPP], const int number)
{
    int fill; /* Increments up to one less than the last string. */
    int index_of_smallest; /* First in alphabetical order. */
    char copy_temp[STRING_SIZE]; /* Holds the capitalized name that is out of order. */
    char * names_temp;
    int * ages_temp;
        
    /* Goal: fill the first row in the array of strings. */
    for (fill = 0; fill < number - 1; ++fill)
    {
        index_of_smallest = alpha_first(names_copy, fill, number);
        
        /* This snippet sorts the arrays.  The program needs to move around the capitalized strings in the 'names_copy[]' array because that is what the comparison statement uses in the 'alpha_first' function, and the program does not need to keep the capitalized string in order.
         The program moves around the memory addresses in the names pointer and the ages pointer so that they can print out an alphabetized list.  Doing so with pointers preserves the order of the original names and ages arrays. */
        if (index_of_smallest != fill)
        {
            /* "Move the smallest one to the side." */
            strcpy(copy_temp, names_copy[index_of_smallest]);
            names_temp = names_pointer[index_of_smallest];
            ages_temp = ages_pointer[index_of_smallest];
            
            /* "Put the bigger one where the smaller one was." */
            strcpy(names_copy[index_of_smallest], names_copy[fill]);
            names_pointer[index_of_smallest] = names_pointer[fill];
            ages_pointer[index_of_smallest] = ages_pointer[fill];
            
            /* "Now put the smallest one into place." */
            strcpy(names_copy[fill], copy_temp);
            names_pointer[fill] = names_temp;
            ages_pointer[fill] = ages_temp;
        }
    }
}

/* Compares capitalized versions of the applicants' names and returns the increment number of which remaining name should be the next "first" in alphabetical order. */
int alpha_first(char names_copy[][STRING_SIZE], const int fill_sub, const int number)
{
    int first;
    int i;
    
    first = fill_sub;
    
    /* Compares second item in the list to the first. */
    for (i = fill_sub + 1; i < number; ++i)
    {
        /* This is comparing the capitalized names. */
        if (strcmp(names_copy[i], names_copy[first]) < 0)
        {
            first = i;
        }
    }
    
    return (first);
}

void display(char * names_pointer[], int * ages_pointer[], const char names[][STRING_SIZE], const int ages[MAXAPP], const int number)
{
    int i;
    
    /* Display's lists. */
    printf("\nOriginal list \n");
    printf("---------------------- \n");
    
    for (i = 0; i < number; ++i)
    {
        printf("%-19s %d\n", names[i], ages[i]);
    }
    printf("\n\n");
    
    printf("Alphabetized list \n");
    printf("----------------------- \n");
    
    for (i = 0; i < number; ++i)
    {
        printf("%-19s %d\n", names_pointer[i], *ages_pointer[i]);
    }
    printf("\n\n");
}


/*
 In this program, the string copy array acts like a messenger between the original list of names and the array pointers.
 It works like this: the 'names_copy[]' starts out the same as the original 'names[]' array.  Then, the program turns it into all capitals so that it can take the copy of the names list back and forth between the alphabetical comparison function and the sorting function, each time bringing with it the increment number of the next name in alphabetical order.
 Using that increment, the program alphabetizes both the capitalized copy of the original AND the parallel array pointers of names ages before it sends back the incrementally more alphabetized copy of the capitalized copy back to the alphabetical comparison function for the NEXT alphabetized increment.
 With that messenger service complete, the program can display the original array, which preserves the order in which people signed up, and the alphabetized pointers that let the users find names more quickly.  The correct ages tag along for the ride.
 Just a note: The program could just send the pointer array to the alphabetizing and sorting functions and get an alphabetized list on some compilers.  But, by sending the capitalized copy to the functions, the program can get an alphabetized list on any compiler.
 */
