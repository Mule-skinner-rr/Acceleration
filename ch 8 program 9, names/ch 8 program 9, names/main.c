//
//  main.c
//  ch 8 program 9, names
//
//  Created by Ryan Roderick on 4/11/21.
//

/* From "Problem Solving and Program Design in C" by Jeri Hanly and Elliot Koffman, 7th Ed., 2013. */

/* page 515 - 516 */

/*
 9. Write a program that processes a data file of names in which each name is on a separate line of at most 80 characters.  Here are two sample names:
 
    Heartman-Montgomery, Jane R.
    Doe, J. D.
 
    On each line, follow the surname by a comma and a space, then the first name or initial and a middle initial.  Your program should scan the names into three arrays--'surname', 'first', and 'middle_init'.  If the surname is longer than 15 characters, store only the first 15.  Similarly, limit the first name to ten characters.  Do not store periods in the 'first' and 'middle_init' arrays.  Write the array's contents to a file, aligning the contents of each column:
 
    Hartman-Montgom     Jane    R
    Doe                 J       D
 */

/* There are two files here to go with the : names.txt and formatted_names.txt.  Feel free to use them if you would like to do a sample run of the program.  Make sure you Working Directory is set to read from their location! */

#include <stdio.h>
#include <string.h>

#define LINE_LENGTH 80
#define SURNAME 16
#define FIRST_NAME 11
#define INITIAL 2
#define MAX_NAMES 100

void get_file_names(char inname[], char outname[]);

int get_lists(char list[][LINE_LENGTH], char list_copy[][LINE_LENGTH], FILE * inp);

void drop_tokens(char * common[], char * last[], char * middle[], char list_copy[][LINE_LENGTH], const char list_length);

void assemble_arrays(char * common[], char * last[], char * middle[], char surname[][SURNAME], char first[][FIRST_NAME], char  middle_init[][INITIAL], const char list_length);

void print_file(FILE * outp, char surname[][SURNAME], char first[][FIRST_NAME], char  middle_init[][INITIAL], const char list_length);

int main(int argc, const char * argv[])
{
    const int name_length = 40;
    char inname[name_length], outname[name_length]; /* The user inputs the text file names, and the program stores them into these variables. */
    FILE * inp, * outp; /* pointers to text files */
    char list[MAX_NAMES][LINE_LENGTH], list_copy[MAX_NAMES][LINE_LENGTH]; /* The program stores the full lists from the file into these string arrays. */
    char * common[MAX_NAMES], * middle[MAX_NAMES], * last[MAX_NAMES];  /* With the help of 'strtok', these will point to sections of each line in the string arrays so that the program can extract first, middle, and last names into separate string arrays. */
    int list_length; /* This is the length of the list from any given input file, which won't be more than MAX_NAMES. */
    char surname[MAX_NAMES][SURNAME], first[MAX_NAMES][FIRST_NAME], middle_init[MAX_NAMES][INITIAL];
    

    get_file_names(inname, outname);
    
    inp = fopen(inname, "r");
    outp = fopen(outname, "w");
    
    if (inp == NULL) {
        printf("inp did not open\n");
        return (0);
    }
    
    list_length = get_lists(list, list_copy, inp);
    
    drop_tokens(common, last, middle, list_copy, list_length);
    
    assemble_arrays(common, last, middle, surname, first, middle_init, list_length);
    
    print_file(outp, surname, first, middle_init, list_length);
    
    fclose(inp);
    fclose(outp);
    
    return 0;
}

/* Populates 'inname' and 'outname'. */
void get_file_names(char inname[], char outname[])
{
    printf("Name of input file> ");
    scanf("%s", inname);
    printf("Name of output file> ");
    scanf("%s", outname);
}

/* page 472 */
/* Using 'fgets' and 'strcpy', this function copies each line from a file that has a list of names in it into 'list[][]' and 'list_copy[][]'. */
int get_lists(char list[][LINE_LENGTH], char list_copy[][LINE_LENGTH], FILE * inp)
{
    char line[LINE_LENGTH];
    char * status;
    int i = 0;
    int list_length;

    for (status = fgets(line, LINE_LENGTH, inp);
         status != 0; /* 'fgets' returns a string argument as it's value, p. 471., or 0, which is considered the null pointer.  That is why the program declares 'status' as a pointer.  */
         status = fgets(line, LINE_LENGTH, inp))
    {
        if (line[strlen(line) -1] == '\n')
        {
            line[strlen(line) - 1] = '\0';
        }
        strcpy(list[i], line);
        strcpy(list_copy[i], line);
        ++i;
    }
    
    list_length = i;

    return(list_length);
}

/* page 465 */
/* Adds tokens to 'list_copy[][]' and assigns pointers to those sections of each string. */
void drop_tokens(char * common[], char * last[], char * middle[], char list_copy[][LINE_LENGTH], const char list_length)
{
    int i;
    
    for (i = 0; i < list_length; ++i)
    {
        last[i] = strtok(list_copy[i], ", .");
        common[i] = strtok(NULL, ", .");
        middle[i] = strtok(NULL, ", .");
    }
}

/* Copies the sections of each list entry into arrays and prints */
void assemble_arrays(char * common[], char * last[], char * middle[], char surname[][SURNAME], char first[][FIRST_NAME], char  middle_init[][INITIAL], const char list_length)
{
    int i;
    
    /* These statements copy the value from the pointer, 'last', 'first', 'middle', into arrays for each item and assign a null character at the end of each. */
    for (i = 0; i < list_length; ++i)
    {
        strncpy(surname[i], last[i], SURNAME);
        surname[i][SURNAME - 1] = '\0';
        
        strncpy(first[i], common[i], FIRST_NAME);
        common[i][FIRST_NAME -1] = '\0';
        
        strncpy(middle_init[i], middle[i], INITIAL);
        middle_init[i][INITIAL - 1] = '\0';
    }
    
}

/* Prints the data to both a file and standard output.  The dashes, '-', in the print statements justify the text left. */
void print_file(FILE * outp, char surname[][SURNAME], char first[][FIRST_NAME], char  middle_init[][INITIAL], const char list_length)
{
    int i;
    
    printf("\n");
    
    for (i = 0; i < list_length; ++i)
    {
        printf("%-20s %-10s %-s \n", surname[i], first[i], middle_init[i]);
        fprintf(outp, "%-20s %-10s %-s \n", surname[i], first[i], middle_init[i]);
    }
    printf("\n");
}

/*
 The key to changing the lines of data into fields is 'strtok'.  It scans each line and drops a null character token, '\0', whenever it encounters one of the delimiters, ', .'.  The program assigns a pointer to each section of the line.  Then, the program can use the pointer to assign that value to its own array.
 I tried so separate these things out with loops, but would have taken many more 'if/else' statements and loops to skip over spaces.  I think that is why they came up with 'strtok'.
 */
