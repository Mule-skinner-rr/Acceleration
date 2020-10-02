//
//  main.c
//  ch 7 program 1.1
//
//  Created by Ryan Roderick on 9/22/20.
//



/* While working on this problem, even getting started on it, I learned from 'nikhilnayak98' on GitHub in his 'CSE2041' repository for the problems in this book that I can deal with the input file one section at a time, instead of writing a loop that would read all of it at once and put all the information in its respective variables or arrays.  So, I owe a special thanks to him. */



/* From "Problem Solving and Program Design in C" by Jeri Hanly and Elliot Koffman, 7th Ed., 2013. */

/* Chapter 7, Programming Projects probelm #1, pages 443-444 */

/* BEGIN QUOTE:
 Write a program to grade an n-question multiple-choice exam (for 'n' between 5 and 50) and provide feedback about the most frequently missed questions.
 
 Your program will take data from the file 'examdat.txt'.
 The first line of the file contains the number of questions on the exam followed by a space and then an n-character string of the correct answers.
 
 Write a function 'fgetAnswers' that inputs the answers from an open input file.
 Each of the lines that follow (in the file) contain an integer student ID followed by a space and then that student's answers.
 
 Function 'fgetAnswers' can also be called to input a student's answers.
 
 Your program is to produce an outputfile, 'report.txt', containing the answer key, each students's ID and each student's percentages as a percentage, and then inofrmation about how many students missed each question.
 
 Here are short sample input and output files.
 
 'examdat.txt'
 5 dbbac
 111 dabac
 102 dcbdc
 251 dbbac
 
 'report.txt'
            Exam Report
 Question   1 2 3 4 5
 Answer     d b b a c
 
  ID    percentages(%)
 111    80
 102    60
 251    100
 
 Question   1 2 3 4 5
 Missed by  0 2 0 1 0
 
 END QUOTE.
 */

#include <stdio.h>
#define MAX_QUESTIONS 50
#define ROSTER 100
/* The question requires that the program is able to grade up to 50 questions. Defining 'ROSTER' as 100 would allow for 100 quiz takers. */


    int get_key(FILE*, char[]);

void fgetAnswers(char[], int, FILE*);

    int get_additional(FILE*, int, int, int[], char[][MAX_QUESTIONS]);

    void get_percentages(char[], char[][MAX_QUESTIONS], int, int, double[], int[]);

    void display_report(int, int, char[], int[], double[], int[]);
/* I indent all of the helper functions in this list. */



int main(int argc, const char * argv[]) {
    
    FILE *input = fopen("examdat_1.1.txt", "r");
    if (input == NULL) {
        perror("'input' didn't open\n");
        return(-1);
    }
    /* I'm declaring '*input' as a pointer to a place in memory that can accept data from the file, "examdat_1.1.txt" and store it into various variables.
     I'm also using an 'if' statement to verify that the file opens.  In simple programs like this one that use the command line in Xcode, I will get an exception error down at the first 'fscanf' function saying that there is a bad thread if the file did not open up with this declaration and assignment.  By verifying that my file assignment worked, I'm giving myself a reminder to set the working directory for the location of the file 'examdat_1.1.txt' if I didn't already.
     To do so in Xcode 11, I go to the tool bar and proceed from Product to Scheme to Edit Scheme and click on that, which opens a drop-down window.  I select 'Options' in that window and click the box by 'Working Directory'.  Then, I click on the little grey icon that looks like a file folder and set the directory to the file in my computer where I'm storing the Xcode project so that the file is connected to this program. */
    
    char key[MAX_QUESTIONS];
    /* This is the array for the key to the quiz.  I can partially fill it for the five multiple-choice questions I have, or up to 50 multiple-choice, character answers, 'a', 'b', 'c', 'd'.  */
    
    int n;
    /* 'n' represents the number of questions for the quiz.  It is the first number that the program will read from the file. */
    
    n = get_key(input, key);
    /* From the 'input' file, this function call returns the number of questions on the quiz and stores it in 'n'.  Then, it fills the 'key' array with the five correct letter choices for the multiple-choice quiz. */
    
    fgetAnswers(key, n, input);
    /* This function call sends down the partially filled array, 'key', with it's five letters recorded in it.  The function also sends down 'n' with the number of quiz questions, 5.  And, it sends down the memory address of the pointer 'input', where the program will store the quiz that it accesses in the file 'examdat_1.1.txt'.  It is important to note that the 'fscanf' function starts at the beginning of the file, reads each item that the program instructs it to, and then stops at that point.  So, after function 'get_key', the 'fscanf' functions's insertion point will be waiting at the end of that line and pick up again at that point when the program again calls the 'fscanf' function, which it can do from anywhere in the program. */
    
    fclose(input);
    
    return(0);
    
}



int get_key(FILE *input, char key[])
{
    int n, i;
    /* 'n' will be the number of questions on whatever quiz the program is processing, and this function will return it to the 'main' function.  Giving it the same name as its counterpart in the 'main' makes the program simpler than it would be if I wrote it in as a pointer.  The varialbe 'i' will serve as an increment variable. */

    char space; /* The 'fscanf' function uses this variable to store the space after the number in the first line of the file, which it needs to do in order to continue through the program.  The program will simply overwrite the variable each time the 'fscanf' function needs to proceed through a space between other characters or numbers.*/
    
    /* These declarations set me up to deal with the first line of the file.  It is already open in a read format, "r". */
    
    fscanf(input, "%d", &n);
    fscanf(input, "%c", &space);
    /* With these two statements, I scan in the first number, which tells me how many questions there are on the quiz, and the space. */
    
    for (i=0; i<n; ++i) {
        fscanf(input, "%c", &key[i]);
    }
    /* Here, I'm using a 'for' loop to scan each letter in succession into the 'key' array.  As 'i' increments from 0, it also increments in the 'key[i]' and moves the compiler to the next spot in the memory it allocated for 'key'.
     Note, the "%c" placeholder for the file scan function, 'fscanf', does not need the extra space in front of it, " %c", like it does for the standard input, 'scanf', function. */
    
    /* While working on this problem, I learned from 'nikhilnayak98' on GitHub.  In his solution to this problem in 'CSE2041', his repository for the problems in this book, I saw that can deal with the input file one section at a time, instead of writing a loop that would read it all at once and put all the information into respective variables or arrays, so I owe a special thanks to him.
     */
    
    return(n);
}



void fgetAnswers(char key[], int n, FILE *input)
{
    /* The 'key' array and variable 'n' are input arguments to this function.  This function extracts more information from the 'FILE *input' pointer. */
    
    int i;
    char j, space;
    int students;
    /* 'i' and 'j' are increment variables and can represent row or column numbers.  'students' is an accumulator variable that the program will use to limit the number of times its loops iterate. */
    
    int id_numbers[ROSTER];
    char responses[ROSTER][MAX_QUESTIONS];
    double percentages[ROSTER];
    /* These variables are pointers to parallel arrays that will hold the data for the output file, 'report_1.1.txt'.  Figuring out how to coordinate these was my main learning experience for this program. */
    
    int missed_by[n];
    /* This accumulator array works with the grid array, 'responses[][]', to accumulate the number of people who got the wrong answer for each of the multiple-choice questions. */
    
    students = 0;
    /* initializing 'students' just before the program uses it makes the program more readable.  The following loop uses the two increment variables, 'i' in the outer loop and 'j' in the inner loop, to populate the grid array 'responses'. */
    
    for (i=0;   (fscanf(input, "%d", &id_numbers[i]) != EOF);   ++i)
    {
        /* As a test condition, this outer 'for' loop scans in the student ID numbers from the file, 'examdat_1.1.txt', into 'id_numbers', which is the first of two parallel arrays, 'id_numbers' and 'responses'.
         When the the program uses the two arrays together, the 'id_numbers' will act as a list of rows in this outer loop, the 'i' variable represents rows. */
        
        fscanf(input, "%c", &space);
        /* The loop scans in the 'space' between the ID number and the responses in order to move the 'fscanf' function forward. */
        
        for(j=0; j<n; j++)
            fscanf(input, "%c", &responses[i][j]);
        /* Now, the inner 'for' loop scans in the letter answers from the file to the columns of the grid array, 'responses', the second of the two parallel arrays.
         The inner loop uses 'j' as an increment value and it represents the columns in each row, so in the grid variable 'responses[i][j]', the 'i' points to the row and the 'j' points to the columns. */
        
        ++students;
        /* Finally, At the end, the loop increments the variable 'students' so that the program can accumulate the total number of students being recorded for this quiz.  Doing so is important because the arrays will usually be partially filled, and the program needs to record the number of quizes recorded in the 'examdat_1.1.txt' file. */
    }
    
    students = get_additional(input, students, n, id_numbers, responses);
    /* This function allows the user in record additional quiz records.  It adds them to the parallel arrays, 'id_numbers', and 'responses', and the 'examdat_1.1.txt' file with the 'fopen' append option, "a".  If any records were added, the function increments the 'students' variable and returns it. */

    get_percentages(key, responses, students, n, percentages, missed_by);
    /* 'get_percentages' gets the 'key' array, the 'responses' grid, the 'students' and 'n' variables.  The function returns the percentages to each of the quizzes as a percent and it counts the number of quiz takers who got each question wrong.  */
    
    display_report(students, n, key, id_numbers, percentages, missed_by);
    /* Function 'display_report' receives the variables 'students' and 'n' as integers that will limit loops to that number of iterations as it displays the 'key', 'id_numbers', 'percentages', and 'missed_by' arrays. */

}




int get_additional(FILE *input, int students, int n, int id_numbers[], char responses[][MAX_QUESTIONS])
{
    char y_or_n;
    int j;
    /* 'students' takes the place of the 'i' increment variable. */
    
    printf("Do you have any quizzes to add?\n");
    printf("Please enter a 'y' or 'n'");
    printf("\n> ");
    scanf(" %c", &y_or_n);
    /* Here, I'm giving function 'getAnswers' the ability to record more students answers from the user. */
    
    if(y_or_n == 'y') {
        
        fclose(input);
        input = fopen("examdat_1.1.txt", "a");
        /* The "a" means append.  This causes the program two write to the end of the file.  Appending any new quizes to the text file while also adding them to the arrays in this program, allows the user to have their additional information recorded after the program ends. */
        
        if(input == NULL)
            perror("input didn't open\n");
        /* checking if 'input' file opened. */
        
        fprintf(input, "\n");
        /* This end line escape sequence, "\n", puts a line break in the 'input' file, which in this case the program is writing to.  The end line escape sequence returns the insertion point to the next line or adds a space before the new input, deptnding where 'fscanf' left off. */
        
        do {
            printf("\nPlease enter the ID# > ");
            scanf("%d", &id_numbers[students]);
            fprintf(input, "%d ", id_numbers[students]);
            /* This 'do/while' loop prompts the user for the student ID number and stores it in the memory location for the 'id_numbers' array.  The variable 'student' has the correct, incremented location. */
            
            printf("Quiz responses > ");
            for (j=0; j<n; ++j) {
                scanf(" %c", &responses[students][j]);
                fprintf(input, "%c", responses[students][j]);
                /* This 'for' loop records the student's quiz responses in each column number that 'j' points to. */
            }
            fprintf(input, "\n");
            /* This new line escape sequence puts a new line in the 'input' file for any additional student numbers and quiz responses. */

            ++students;
            /* increments 'students' */
            
            printf("Do you have any more percentages to enter?\n");
            printf("Please enter 'y' or 'n'> ");
            scanf(" %c", &y_or_n);
            /* This prompt gives the user to opt to add more information to the program or exit the loop. */
            
        } while(y_or_n == 'y');
        
        fclose(input);
    }
    
    return(students);
    /* The 'return' statement provides the new total number of 'students' for other loops in the program. */
}



void get_percentages(char key[], char responses[][MAX_QUESTIONS], int students, int n, double percentages[], int missed_by[])
{
    int i, j, correct;
    /* The program uses local variables 'i' and 'j' in two 'for' loops to compare each answer in the 'key' array to each answer in the 'responses' grid.  It accumulates the correct responses in 'correct' and the incorrect responses in the 'missed_by' array. */
    
    for(j=0; j<n; ++j) {
        missed_by[j] = 0;
    }
    /* This 'for' loop initializes the 'missed_by[j]' array, which uses the 'j' increment because of its location in the series of loops below.  The program initializes it to '0' because if the values in its memory locations don't change, the program needs them to print out to '0'. */
    
    correct = 0;
    /* The program initializes 'correct' because it will play a role in the next loop. */
    for (i=0; i<students; ++i) {
        for (j=0; j<n; ++j) {
            if (key[j] == responses[i][j]) {
                ++correct;
            } else {
                ++missed_by[j];
            }
        }
        percentages[i] = (correct * 100) / n;
        correct=0;
    }
    /* The easiest part of this loop to code incorrectly is the 'if/else' decision statement.  It compares 'key[j]' to 'responses[i][j]'.  'i' represents the row of this comparison, and it will correspond to the increment for student 'id_numbers', which will also correspond to the increment for the 'percentages' recorded for each quiz.
     The 'i' is set in the outer loop so that the inner loop can compare the series of letters in 'key[j]' to the series of letters in the columns of each row of 'responses[i][j]'.
     The 'missed_by[j]' array also uses the 'j' variable because it will count up each time the question in that column was answered incorrectly.  'missed_by[j]' needs to accumulate this number in order to print it out in the output file.
     'correct++' accumulates the number of correct responses in order to calculate that student's score.  The program calculates the students 'percentage' score and stores it in the 'percentages[i]' array just after the inner loop exits and before the outer loop increments to the next student, which is why the 'percentages[i]' array uses the 'i' increment and not the 'j'.
     Once the calculation is complete and stored in the 'percentages' array, 'correct=0;' reinitializes 'correct' to '0' so that it is ready for the calculation for the next student's percentage. */
}



void display_report(int students, int n, char key[], int id_numbers[], double percentages[], int missed_by[])
{
    FILE *output = fopen("report_1.1.txt", "w");
    /* Simultaneously declaring 'FILE *output' and assigning it with 'fopen("report_1.1.txt", "w")' as a "write to" pointer, "w". */

    int i;
    /* The three parallel, single dimensional arrays in this function only need one increment variable, 'i'. */
    
    fprintf(output, "\t  Exam Report \n");
    fprintf(output, "Question  ");
    for (i=0; i<n; ++i)
        fprintf(output, "%d ", i+1);
    /* Prints the first line heading and the next line label followed by a series of integers to indicate the question number.  The tab escape sequences, '\t', print a tab. */
    
    fprintf(output, "\nAnswer    ");
    for (i=0; i<n; i++)
        fprintf(output, "%c ", key[i]);
    fprintf(output, "\n\n");
    /* Prints the 'Answer' label followed by the correct answers in the 'key' array.  The double new line escape sequences, '\n', print two new lines after the loop exits. */
    
    fprintf(output, "ID \t   Socres(%%) \n");
    for (i=0; i<students; ++i)
        fprintf(output, "%d \t    %.0f\n", id_numbers[i], percentages[i]);
    fprintf(output, "\n");
    /* Prints the labels for the student IDs and their percentage correct. */
    
    fprintf(output, "Question   ");
    for (i=0; i<n; ++i)
        fprintf(output, "%d ", i+1);
    /* Prints the 'Question' label and the series of integers for the question numbers. */
    
    fprintf(output, "\nMissed by  ");
    for (i=0; i<n; ++i)
        fprintf(output, "%d ", missed_by[i]);
    fprintf(output, "\n");
    /* Prints the 'Missed by' label and the number of students that missed that question with the 'missed_by' array. */
}
